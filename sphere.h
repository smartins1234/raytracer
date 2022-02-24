#ifndef SPHERE_H
#define SPHERE_H

#include "shape.h"
#include "shader.h"
#include "returnInfo.h"

using namespace std;

class sphere : public shape
{
public:
    vec *center;
    float radius;
    shader *color;

    sphere(vec *c, float r, shader *s);

    returnInfo *hitShape(ray *r, bool prim);
};

#endif /* SPHERE_H */ 
