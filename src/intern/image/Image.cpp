#include "image/Image.h"

using namespace recartyar;

Image::Image(int width, int height) {
    initiate(width, height);
}

Image::~Image() {
    clear();
}

void Image::resize(int width, int height) {
    clear();
    initiate(width, height);
}

Color Image::getRawColor(int x, int y) {
    return pixels[y * width + x];
}

Color Image::getColor(int x, int y) {
    if (addCounts[y * width + x] == 0) {
        return pixels[y * width + x];
    }
    else {
        return pixels[y * width + x] / addCounts[y * width + x];
    }
}

void Image::setColor(int x, int y, Color color) {
    pixels[y * width + x] = color;
    addCounts[y * width + x] = 0;
}

void Image::addColor(int x, int y, Color color) {
    pixels[y * width + x] += color;
    addCounts[y * width + x]++;
}

void Image::blur(int n) {

    /* Your Work Here (Section 3.4.1) */
    int filter[n * n];
    float filter_[n * n];

    int mid = n / 2;
    float min = std::numeric_limits<float>().max();
    float sigma = std::floor(n / 2.0f) / 2.0f;
    int sum = 0;

    for (int x = -mid; x <= mid; x++) {
        for (int y = -mid; y <= mid; y++) {
            int x_ = x + mid;
            int y_ = y + mid;
            filter_[x_ + y_*n] = (1 / (std::sqrt(2 * pi) * sigma)) * std::exp((-x * x) / (2 * sigma * sigma))
                               * (1 / (std::sqrt(2 * pi) * sigma)) * std::exp((-y * y) / (2 * sigma * sigma));
            if (filter_[x_ + y_*n] < min) min = filter_[x_ + y_*n];
        }
    }

    for(int x=0; x<n; x++) {
        for(int y=0; y<n; y++) {
            filter[x + y*n] = std::floor(filter_[x + y*n]/min);
            sum += filter[x + y * n];
        }
    }

    convolve(filter, n, sum, 0);
}

void Image::convolve(int * filter, int n, int normalization, int absval) {
    int mid = n / 2;
    Color * newPixels = new Color[width * height];
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            float r = 0, g = 0, b = 0;
            Color & p = newPixels[i + width * j];
            if ((mid <= i && i < width - mid) && (mid <= j && j < height - mid)) {
                for (int u = 0; u < n; u++) {
                    for (int v = 0; v < n; v++) {
                        r += filter[u + n * v] * getColor(i - mid + u, j - mid + v).r;
                        g += filter[u + n * v] * getColor(i - mid + u, j - mid + v).g;
                        b += filter[u + n * v] * getColor(i - mid + u, j - mid + v).b;
                    }
                }
            }
            else {
                //check what pixels are missing
                for (int u = 0; u < n; u++) {
                    for (int v = 0; v < n; v++) {
                        int i_, j_, i_mirror, j_mirror;
                        i_ = i - mid + u;
                        j_ = j - mid + v;
                        i_mirror = i + mid - u;
                        j_mirror = j + mid - v;
                        if ((i_ < 0 || i_ >= width) && (0 <= j_ && j_ < height)) {
                            r += filter[u + n * v] * getColor(i_mirror, j_).r;
                            g += filter[u + n * v] * getColor(i_mirror, j_).g;
                            b += filter[u + n * v] * getColor(i_mirror, j_).b;
                        }
                        else if ((0 <= i_ && i_ < width) && (j_ < 0 || j_ >= height)) {
                            r += filter[u + n * v] * getColor(i_, j_mirror).r;
                            g += filter[u + n * v] * getColor(i_, j_mirror).g;
                            b += filter[u + n * v] * getColor(i_, j_mirror).b;
                        }
                        else if ((i_ < 0 || i_ >= width) && (j_ < 0 || j_ >= height)){
                            r += filter[u + n * v] * getColor(i_mirror, j_mirror).r;
                            g += filter[u + n * v] * getColor(i_mirror, j_mirror).g;
                            b += filter[u + n * v] * getColor(i_mirror, j_mirror).b;
                        }
                        else {
                            r += filter[u + n * v] * getColor(i_, j_).r;
                            g += filter[u + n * v] * getColor(i_, j_).g;
                            b += filter[u + n * v] * getColor(i_, j_).b;
                        }
                    }
                }
            }
            if (absval == 0) {
                p.r = r / normalization;
                p.g = g / normalization;
                p.b = b / normalization;
            }
            else {
                p.r = std::abs(r) / normalization;
                p.g = std::abs(r) / normalization;
                p.b = std::abs(r) / normalization;
            }
        }
    }
    delete[] pixels;
    pixels = newPixels;
}

bool Image::save(const char * filename) {
    
    // Initiate
    int numPixels = width * height;
    int* intPixels = new int[numPixels];
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            intPixels[i + width * j] = getColor(i, j).toInt();
        }
    }
    
    // Setup Header
    BitmapHeader head;
    head.fileSize = sizeof(BitmapHeader) + 2 + numPixels * sizeof(int);
    head.reserved = 0;
    head.startAddress = sizeof(BitmapHeader) + 2;
    head.headerSize = 12;
    head.width = width;
    head.height = height;
    head.colorPlanes = 1;
    head.bitsPerPixel = 32;
    
    // Start to write files
    FILE * f = fopen(filename, "wb");
    if (f == 0) {
        printf("Can't open '%s'\n", filename);
        return false;
    }
    short magic = 19778;
    fwrite(&magic, sizeof(short), 1, f);
    fwrite(&head, sizeof(BitmapHeader), 1, f);
    fwrite(intPixels, sizeof(int), numPixels, f);
    fclose(f);
	delete [] intPixels;
    return true;
}

void Image::clear() {
    delete [] pixels;
    delete [] addCounts;
}

void Image::initiate(int width, int height) {
    this->width = width;
    this->height = height;
    this->pixels = new Color[width * height];
    this->addCounts = new int[width * height];
    for (int i = 0; i < width * height; i++) {
        addCounts[i] = 0;
    }
}
