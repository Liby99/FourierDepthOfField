#ifndef QUASI_SAMPLER_H
#define QUASI_SAMPLER_H

#include <math.h>
#include <vector>

namespace quasisampler {

#define MIN(x, y) ((x)<(y)?(x):(y))
#define MAX(x, y) ((x)>(y)?(x):(y))

#define LUT_SIZE 21 // Number of Importance Index entries in the Lookup table.
#define NUM_STRUCT_INDEX_BITS 6 // Number of significant bits taken from F-Code.

#define GOLDEN_RATIO PHI // Phi is the Golden Ratio.
#define PHI     1.6180339887498948482045868343656 // ( 1 + sqrt(5) ) / 2
#define PHI2    2.6180339887498948482045868343656 // Phi squared
#define LOG_PHI 0.48121182505960347 // log(Phi)
#define SQRT5   2.2360679774997896964091736687313 // sqrt(5.0)

    // Two-bit sequences.
#define B00 0
#define B10 1
#define B01 2

    enum TileType {
        TileTypeA,
        TileTypeB,
        TileTypeC,
        TileTypeD,
        TileTypeE,
        TileTypeF
    };

    class Point2D {
    public:
        double x, y;

        Point2D() {};

        Point2D(const double x, const double y) {
            this->x = x;
            this->y = y;
        }

        Point2D(const double vect[2]) {
            x = vect[0];
            y = vect[1];
        }

        Point2D operator+(const Point2D &pt) const { return Point2D(x + pt.x, y + pt.y); }

        Point2D operator-(const Point2D &pt) const { return Point2D(x - pt.x, y - pt.y); }

        Point2D operator*(double factor) const { return Point2D(x * factor, y * factor); }

        Point2D operator/(double factor) const { return Point2D(x / factor, y / factor); }

        /// Returns the squared distance to the origin, or the squared length of a vector.
        double d2() const;
    };

    class QuasiSampler {
    protected:

        static const unsigned fiboTable[32];
        static const Point2D vvect[20];
        static const double lut[LUT_SIZE][21][2];

        static unsigned fibonacci(unsigned i) {
            if (i < 1) return 1;
            if (i <= 32) return fiboTable[i - 1]; // pre-calculated.
            return fibonacci(i - 1) + fibonacci(i - 2);
        }

        static unsigned getReqSubdivisionLevel(unsigned importance) {
            if (importance == 0) return 0;
            unsigned nbits = (unsigned) (log((double) importance * SQRT5 + 1.0) / LOG_PHI) - 1;
            if (nbits < 1) nbits = 1;
            return (unsigned) ceil(0.5 * nbits);
        }

        static unsigned calcFCodeValue(unsigned bitsequence, unsigned nbits) {
            unsigned i_s = 0;
            for (unsigned i = 0; i < nbits; i++) {
                if (bitsequence & (1u << (nbits - i - 1))) i_s += fibonacci(i + 2);
            }
            return i_s;
        }

        static unsigned calcStructuralIndex(unsigned bitsequence) {
            return calcFCodeValue(bitsequence, NUM_STRUCT_INDEX_BITS);
        }

        /// Returns the Importance Index (i_v) for a given importance value.
        /// The value returned is \f$ \lfloor n \cdot ({\log_{\phi^2} \sqrt{5} \cdot x}) ~ {\bf mod} ~ 1 \rfloor \f$.
        static unsigned calcImportanceIndex(unsigned importance) {
            double t = log(1.0 + sqrt(5.0) * importance) / log(PHI2);
            t -= floor(t); // modulo 1.0
            return (unsigned) (LUT_SIZE * t);
        }


        /// Fetches the appropriate vector from the lookup table.
        static Point2D calcDisplacementVector(unsigned importance, unsigned f_code, int dir) {
            unsigned i_s = calcStructuralIndex(f_code);
            unsigned i_v = calcImportanceIndex(importance);

            return
                    vvect[dir] * lut[i_v][i_s][0] + // u component
                    vvect[(dir + 5) % 20] * lut[i_v][i_s][1]; // v component
        }


        //
        // Inner classes.
        //


        /// Individual tile elements, which also serve as nodes for the tile subdivision tree.
        class TileNode {

            unsigned level; // Depth in the tree.
            int tileType; // Types A through F.
            int dir; // Tile orientation, 0=North, in Pi/10 increments, CCW.
            double scale;
            Point2D p1, p2, p3; // Three points of the triangle. Counter-clockwise.

            /// The F-Code binary sequence.
            unsigned f_code;

            // tiling tree structure
            TileNode *parent;
            unsigned parent_slot; // position in parent's list (needed for iterators)
            bool terminal; // true for leaf nodes
            std::vector<TileNode *> children;

        public:

            /// Builds a tile according to the given specifications.
            TileNode(
                    TileNode *parent = NULL,
                    int tileType = TileTypeF,
                    Point2D refPt = Point2D(0, 0),
                    int dir = 15, // 15 = East.
                    unsigned newbits = 0,
                    int parent_slot = 0,
                    double scale = 1.0) {
                this->parent = parent;
                this->tileType = tileType;
                this->p1 = refPt;
                this->dir = dir % 20;
                this->parent_slot = parent_slot;
                this->scale = scale;
                this->level = parent ? parent->level + 1 : 0; // Increment the level.


                // Build triangle, according to type.
                switch (tileType) {
                    case TileTypeC:
                    case TileTypeD:
                        // "Skinny" triangles
                        p2 = p1 + vvect[dir % 20] * scale;
                        p3 = p1 + vvect[(dir + 4) % 20] * (PHI * scale);
                        break;
                    case TileTypeE:
                    case TileTypeF:
                        // "Fat" triangles
                        p2 = p1 + vvect[dir % 20] * (PHI2 * scale);
                        p3 = p1 + vvect[(dir + 2) % 20] * (PHI * scale);
                        break;
                    default:
                        // Pentagonal tiles (triangle undefined)
                        p2 = p1 + vvect[dir % 20] * scale;
                        p3 = p1 + vvect[(dir + 5) % 20] * scale;
                }

                // Append 2 new bits to the F-Code.
                if (parent)
                    f_code = (parent->f_code << 2) ^ newbits;
                else
                    f_code = newbits;

                // Set as leaf node
                terminal = true;
                children.clear();
            }

            /// Helper constructor.
            /// Creates an initial tile that is certain to contain the ROI.
            /// The starting tile is of type F (arbitrary).
            TileNode(double roi_width, double roi_height) {
                double side = MAX(roi_width, roi_height);
                double scale = 2.0 * side;
                Point2D offset(PHI * PHI / 2.0 - 0.25, 0.125);
                *this = TileNode(NULL, TileTypeF, offset * -scale, 15, 0, 0, scale);
            }

            ~TileNode() { collapse(); }

            /// Splits a tile according to the given subdivision rules.
            /// Please refer to the code for further details.
            void refine() {
                if (!terminal) return; // Can only subdivide leaf nodes.

                terminal = false; // The tile now has children.
                double newscale = scale / GOLDEN_RATIO; // The scale factor between levels is constant.

                switch (tileType) {

                    // Each new tile is created using the following information:
                    // A pointer to its parent, the type of the new tile (a through f),
                    // the origin of the new tile, the change in orientation of the new tile with
                    // respect to the parent's orientation, the two bits to be pre-pended to the F-Code,
                    // the parent's slot (for traversal purposes), and the new linear scale of the tile,
                    // which is always the parent's scale divided by the golden ratio.

                    case TileTypeA:
                        children.push_back(
                                new TileNode(this, TileTypeB, p1, dir + 0, B00, 0, newscale));
                        break;

                    case TileTypeB:
                        children.push_back(
                                new TileNode(this, TileTypeA, p1, dir + 10, B00, 0, newscale));
                        break;

                    case TileTypeC:
                        children.push_back(
                                new TileNode(this, TileTypeF, p3, dir + 14, B00, 0, newscale));
                        children.push_back(
                                new TileNode(this, TileTypeC, p2, dir + 6, B10, 1, newscale));
                        children.push_back(
                                new TileNode(this, TileTypeA, children[0]->p3, dir + 1, B10, 2, newscale));
                        break;

                    case TileTypeD:
                        children.push_back(
                                new TileNode(this, TileTypeE, p2, dir + 6, B00, 0, newscale));
                        children.push_back(
                                new TileNode(this, TileTypeD, children[0]->p3, dir + 14, B10, 1, newscale));
                        break;

                    case TileTypeE:
                        children.push_back(
                                new TileNode(this, TileTypeC, p3, dir + 12, B10, 0, newscale));
                        children.push_back(
                                new TileNode(this, TileTypeE, p2, dir + 8, B01, 1, newscale));
                        children.push_back(
                                new TileNode(this, TileTypeF, p1, dir + 0, B00, 2, newscale));
                        children.push_back(
                                new TileNode(this, TileTypeA, children[0]->p2, dir + 7, B10, 3, newscale));
                        break;

                    case TileTypeF:
                        children.push_back(
                                new TileNode(this, TileTypeF, p3, dir + 12, B01, 0, newscale));
                        children.push_back(
                                new TileNode(this, TileTypeE, children[0]->p3, dir + 0, B00, 1, newscale));
                        children.push_back(
                                new TileNode(this, TileTypeD, children[1]->p3, dir + 8, B10, 2, newscale));
                        children.push_back(
                                new TileNode(this, TileTypeA, children[0]->p3, dir + 15, B01, 3, newscale));
                        break;
                }
            }

            /// Prunes the subdivision tree at this node.
            void collapse() {
                // Recursively prune the tree.
                for (unsigned i = 0; i < children.size(); i++) delete children[i];
                terminal = true;
                children.clear();
            }

            /// Returns the next node of the tree, in depth-first traversal.
            /// Returns NULL if it is at the last node.
            TileNode *nextNode() {
                if (!terminal) return children[0];

                if (level == 0) return NULL; // single node case.

                if (parent_slot < parent->children.size() - 1)
                    return parent->children[parent_slot + 1];

                // last child case
                TileNode *tmp = this;
                do {
                    tmp = tmp->parent;
                } while ((tmp->level != 0) && (tmp->parent_slot == tmp->parent->children.size() - 1));

                if (tmp->level == 0) return NULL; // last node
                return tmp->parent->children[tmp->parent_slot + 1];

            }

            /// Returns the next closest leaf to a node.
            /// Returns NULL if it's the last leaf.
            TileNode *nextLeaf() {
                TileNode *tmp = this;
                do {
                    tmp = tmp->nextNode();
                    if (!tmp) return NULL;
                    if (tmp->terminal) return tmp;
                } while (1);
            }

            // Public accessors

            Point2D getP1() const { return p1; }

            Point2D getP2() const { return p2; }

            Point2D getP3() const { return p3; }

            Point2D getCenter() const { return (p1 + p2 + p3) / 3.0; }

            unsigned getFCode() const { return f_code; }

            bool isSamplingType() const {
                return ((tileType == TileTypeA) || (tileType == TileTypeB));
            }

            unsigned getLevel() { return level; }

            bool isTerminal() const { return terminal; }

            TileNode *getParent() { return parent; }

            TileNode *getChild(unsigned i) { return children[i]; }

            /// Obtains the correction vector from the lookup table,
            /// then scales and adds it to the reference point.
            Point2D getDisplacedSamplingPoint(unsigned importance) {
                return p1 + calcDisplacementVector(importance, f_code, dir) * scale;
            }

        }; // end of class TileNode.

        /// Leaf iterator for the tile subdivision tree.
        /// The traversal is made in a depth-first manner.
        /// Warning: This does not behave like STL style iterators.
        class TileLeafIterator {
            TileNode *shape;
        public:
            TileLeafIterator() { shape = NULL; }

            TileLeafIterator(TileNode *s) { begin(s); }

            TileNode *operator*() { return shape; }

            TileNode *operator->() { return shape; }

            void begin(TileNode *s) {
                TileNode *tmp = s;
                while (!tmp->isTerminal()) tmp = tmp->getChild(0); // find first leaf
                shape = tmp;
            }

            /// Subdivides the tile and moves to its 1st child.
            void refine() {
                shape->refine();
                shape = shape->getChild(0);
            }

            /// Prunes the subdivision tree.
            void collapse() {
                if (shape->getParent()) {
                    shape = shape->getParent();
                    shape->collapse();
                }
            }

            /// Moves to the next node in the subdivision tree, in depth-first traversal.
            /// Returns false iff there is no such node.
            bool next() {
                TileNode *s = shape->nextLeaf();
                if (s) {
                    shape = s;
                    return true;
                } else {
                    shape = s;
                    return false;
                }
            }

            /// Checks if there is a next tile, in depth-first traversal.
            bool hasNext() {
                TileNode *s = shape->nextLeaf();
                if (s) return true;
                else return false;
            }
        };


        //
        // Instance members.
        //

        /// Root node of the tile subdivision tree.
        TileNode *root;

        /// Extents of the region of interest.
        double width, height;

        /// Protected constructor, which initializes the Region of Interest.
        QuasiSampler(double width = 0.0, double height = 0.0) {
            this->width = width;
            this->height = height;
            root = NULL;
        }

        virtual ~QuasiSampler() { if (root) delete root; }


        /// This is a helper function which constrains the incoming points
        /// to the region of interest.
        unsigned getImportanceAt_bounded(Point2D pt) {
            if (pt.x >= 0 && pt.x < width && pt.y >= 0 && pt.y < height)
                return getImportanceAt(pt);
            else
                return 0;
        }

        /// Subdivides all tiles down a level, a given number of times.
        void subdivideAll(int times = 1) {
            if (!root) return;
            TileNode *tmp;
            for (int i = 0; i < times; i++) {
                TileLeafIterator it(root);
                do {
                    tmp = *it;
                    it.next();
                    tmp->refine();
                } while (*it);
            }
        }

        /// Generates the hierarchical structure.
        void buildAdaptiveSubdivision(unsigned minSubdivisionLevel = 6) {
            root = new TileNode(width, height);

            // Since we are approximating the MAX within each tile by the values at
            // a few key points, we must provide a sufficiently dense initial
            // tiling. This would not be necessary with a more thorough scan of each
            // tile.
            subdivideAll(minSubdivisionLevel);

            TileLeafIterator it(root);
            TileNode *tmp;

            // Recursively subdivide all triangles until each triangle's
            // required level is reached.
            unsigned level;
            do {
                level = it->getLevel();

                if (it->isSamplingType()) // Sampling tiles are infinitesimal
                {
                    if (level < getReqSubdivisionLevel(getImportanceAt_bounded(it->getP1()))) {
                        tmp = *it;
                        tmp->refine();
                    }
                } else {
                    if (
                            (level < getReqSubdivisionLevel(getImportanceAt_bounded(it->getP1()))) ||
                            (level < getReqSubdivisionLevel(getImportanceAt_bounded(it->getP2()))) ||
                            (level < getReqSubdivisionLevel(getImportanceAt_bounded(it->getP3()))) ||
                            (level < getReqSubdivisionLevel(getImportanceAt_bounded(it->getCenter())))
                            ) {
                        tmp = *it;
                        tmp->refine();
                    }
                }
            } while (it.next());
        }


        /// Collect the resulting point set.
        void collectPoints(
                std::vector<Point2D> &pointlist,
                bool filterBounds = true) {
            pointlist.clear();

            Point2D pt, pt_displaced;
            unsigned importance;
            TileLeafIterator it(root);
            do {
                pt = it->getP1();
                if (it->isSamplingType()) // Only "pentagonal" tiles generate sampling points.
                {
                    importance = getImportanceAt_bounded(pt);

                    // Threshold the function against the F-Code value.
                    if (importance >= calcFCodeValue(it->getFCode(), 2 * it->getLevel())) {
                        // Get the displaced point using the lookup table.
                        pt_displaced = it->getDisplacedSamplingPoint(importance);

                        if (!filterBounds ||
                            (pt_displaced.x >= 0 && pt_displaced.x < width &&
                             pt_displaced.y >= 0 && pt_displaced.y < height)) {
                            pointlist.push_back(pt_displaced); // collect point.
                        }
                    }
                }

            } while (it.next());

        }

    public:

        /// This virtual function must be implemented in order to use the sampling system.
        /// It should return the value of the importance function at the given point.
        virtual unsigned getImportanceAt(Point2D pt) = 0;

        /// Builds and collects the point set generated be the sampling system,
        /// using the previously defined importance function.
        std::vector<Point2D> getSamplingPoints() {
            if (root) delete root;
            std::vector<Point2D> pointlist;

            buildAdaptiveSubdivision();
            collectPoints(pointlist);
            return pointlist;
        }
    };
}

#endif
