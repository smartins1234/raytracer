#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <vector>

#include "shape.h"
#include "vec.h"
#include "vec2.h"
#include "returnInfo.h"
#include "shader.h"

using namespace std;

class triangle : public shape
{
public:
    vec *a;
    vec *b;
    vec *c;
    shader *color;

    triangle(vec *u, vec *v, vec *n, shader *col);

    vec *getNorm();

    bool inPoly(vec *point, vec *norm);

    returnInfo *hitShape(ray *r, bool prim);
};

#endif /* TRIANGLE_H */ 
