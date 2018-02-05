#ifndef COLOR_H
#define COLOR_H

#include "util/Transform.h"

#include <iostream>
#include <string>

using namespace std;

class Color {
private:
    
    const static float MAX;
    const static float DEFAULT_R;
    const static float DEFAULT_G;
    const static float DEFAULT_B;
    
    // Local variables
    float r;
    float g;
    float b;
    
public:
    
    const static Color WHITE;
    const static Color BLACK;
    const static Color RED;
    const static Color GREEN;
    const static Color BLUE;
    
    // Constructors
    Color();
    Color(float r, float g, float b);
    
    // Getters
    float getR();
    float getG();
    float getB();
    
    // To int version
    int getIntR();
    int getIntG();
    int getIntB();
    
    // Setters
    void setR(float r);
    void setG(float g);
    void setB(float b);
    
    // To Int representation for bitmap
    int toInt();
    
    // Operators
    Color operator+(Color c);
    Color & operator+=(Color c);
    Color operator-(Color c);
    Color & operator-=(Color c);
    Color operator*(Color c);
    Color & operator*=(Color c);
    Color operator*(float scale);
    Color & operator*=(float scale);
    Color operator/(int count);
    Color & operator/=(int count);
    operator string();
    
    static Color parse(int c);
    
    bool operator==(const Color & c) const;
    bool operator!=(const Color & c) const;
    
    friend std::ostream& operator<< (std::ostream & stream, Color & color);
};

typedef Color rgb;

#endif
