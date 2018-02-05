#ifndef GRID_CLONER_H
#define GRID_CLONER_H

#include "object/Cloner.h"

class GridCloner : public Cloner {
protected:
    
    float width;
    float height;
    float length;
    
    int xCount;
    int yCount;
    int zCount;
    
    void construct();
    
public:
    
    GridCloner(Object & object);
    GridCloner(Object & object, float w, float h, float l, int x, int y, int z);
    
    float getWidth();
    float getHeight();
    float getLength();
    
    void setWidth(float width);
    void setHeight(float height);
    void setLength(float length);
    
    int getXCount();
    int getYCount();
    int getZCount();
    
    void setXCount(int xCount);
    void setYCount(int yCount);
    void setZCount(int zCount);
};

#endif
