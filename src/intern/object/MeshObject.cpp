#include "object/MeshObject.h"

using namespace recartyar;

MeshObject::MeshObject() : Object() {}

MeshObject::MeshObject(const char * filename) {
    loadPly(filename);
    smooth();
}

MeshObject::~MeshObject() {
    clear();
}

int MeshObject::addVertex(vec3 position) {
    vertices.push_back(new Vertex(position));
    return vertices.size() - 1;
}

int MeshObject::addVertex(vec3 position, vec3 normal) {
    vertices.push_back(new Vertex(position, normal));
    return vertices.size() - 1;
}

int MeshObject::addTriangle(int i0, int i1, int i2) {
    triangles.push_back(new Triangle(vertices[i0], vertices[i1], vertices[i2]));
    return triangles.size() - 1;
}

void MeshObject::clear() {
    clearVertices();
    clearTriangles();
}

void MeshObject::clearVertices() {
    for (int i = 0; i < vertices.size(); i++) {
        delete vertices[i];
    }
    vertices = std::vector<Vertex *>();
}

void MeshObject::clearTriangles() {
    for (int i = 0; i < triangles.size(); i++) {
        delete triangles[i];
    }
    triangles = std::vector<Triangle *>();
}

bool MeshObject::loadPly(const char * filename) {
    
    // Open file
    FILE * f = fopen(filename,"r");
    if (f == 0) {
        printf("ERROR: MeshObject::LoadPLY()- Can't open '%s'\n",filename);
    }
    
    // Read header
    char tmp[256];
    int numverts = 0, numtris = 0;
    int posprop = -99, normprop = -99;
    int props = 0;
    while (1) {
        fgets(tmp,256,f);
        if (strncmp(tmp, "element vertex", 14) == 0) {
            numverts=atoi(&tmp[14]);
        }
        if (strncmp(tmp, "element face", 12) == 0) {
            numtris=atoi(&tmp[12]);
        }
        if (strncmp(tmp, "property", 8) == 0) {
            int len=strlen(tmp);
            if (strncmp(&tmp[len - 3], " x", 2) == 0) {
                posprop=props;
            }
            if (strncmp(&tmp[len - 3],"nx",2) == 0) {
                normprop=props;
            }
            props++;
        }
        if (strcmp(tmp, "end_header\n") == 0) {
            break;
        }
    }
    
    // Check position properly
    if (posprop == -1) {
        printf("ERROR: MeshObject::LoadPLY() - No vertex positions found\n");
        fclose(f);
        return false;
    }
    
    // Read verts
    int i = 0;
    if (numverts > 0) {
        for (i = 0; i < numverts; i++) {
            fgets(tmp, 256, f);
            char * pch = strtok(tmp, " ");
            int prop = 0;
            vec3 pos, norm;
            while (pch) {
                if (prop == posprop) pos.x = float(atof(pch));
                if (prop == posprop + 1) pos.y = float(atof(pch));
                if (prop == posprop + 2) pos.z = float(atof(pch));
                if (prop == normprop) norm.x = float(atof(pch));
                if (prop == normprop + 1) norm.y = float(atof(pch));
                if (prop == normprop + 2) norm.z = float(atof(pch));
                pch = strtok(0, " ");
                prop++;
            }
            addVertex(pos, norm);
        }
    }

    // Read tris
    if (numtris > 0) {
        for (i = 0; i < numtris; i++) {
            int count, i0, i1, i2;
            fscanf(f, "%d %d %d %d\n", &count, &i0, &i1, &i2);
            if (count != 3) {
                printf("ERROR: MeshObject::LoadPLY()- Only triangles are supported\n");
                fclose(f);
                return false;
            }
            addTriangle(i0, i1, i2);
        }
    }
    
    // Smooth
    if (normprop < 0) {
        smooth();
    }
    
    // Close file
    fclose(f);
    printf("Loaded %lu vertices and %lu triangles from file '%s'\n", vertices.size(), triangles.size(), filename);
}

void MeshObject::smooth() {
    int i, j;
    for (i = 0; i < vertices.size(); i++) {
        vertices[i]->setNormal(vec3(0));
    }
    for (i = 0; i < triangles.size(); i++) {
        Triangle & tri = *triangles[i];
        vec3 e1 = tri.getVertex(2).getPosition() - tri.getVertex(0).getPosition();
        vec3 e2 = tri.getVertex(1).getPosition() - tri.getVertex(0).getPosition();
        vec3 c = cross(e1, e2);
        for (j = 0; j < 3; j++) {
            tri.getVertex(j).addUnnormalized(c);
        }
    }
    for (i = 0; i < vertices.size(); i++) {
        vertices[i]->normalize();
    }
}

void MeshObject::getCorner(vec3 minCorner, vec3 maxCorner) {
    for (int i = 0; i < vertices.size(); i++) {
        minCorner = BoundingBox::minVec(minCorner, vertices[i]->getPosition());
        maxCorner = BoundingBox::maxVec(maxCorner, vertices[i]->getPosition());
    }
}

bool MeshObject::updateIntersect(Ray & ray, Intersection & intersection) {
    bool hit = false;
    for (int i = 0; i < triangles.size(); i++) {
        if (triangles[i]->intersect(ray, intersection)) {
            hit = true;
        }
    }
    return hit;
}

void MeshObject::getBoundingVertices(std::vector<vec3> & verts) {
    vec3 minCorner;
    vec3 maxCorner;
    getCorner(minCorner, maxCorner);
    verts.push_back(vec3(maxCorner.x, maxCorner.y, maxCorner.z));
    verts.push_back(vec3(maxCorner.x, maxCorner.y, minCorner.z));
    verts.push_back(vec3(maxCorner.x, minCorner.y, maxCorner.z));
    verts.push_back(vec3(maxCorner.x, minCorner.y, minCorner.z));
    verts.push_back(vec3(minCorner.x, maxCorner.y, maxCorner.z));
    verts.push_back(vec3(minCorner.x, maxCorner.y, minCorner.z));
    verts.push_back(vec3(minCorner.x, minCorner.y, maxCorner.z));
    verts.push_back(vec3(minCorner.x, minCorner.y, minCorner.z));
}
