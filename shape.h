#ifndef SHAPE_H
#define SHAPE_H

#include "ray.h"
#include "returnInfo.h"

using namespace std;

class shape
{
public:
    virtual returnInfo *hitShape(ray *r, bool prim) {return NULL;}
};

#endif /* SHAPE_H */ 
