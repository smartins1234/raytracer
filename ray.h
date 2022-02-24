#ifndef RAY_H
#define RAY_H

#include "vec.h"

using namespace std;

class ray
{
public:
    vec *origin;
    vec *direction;

    ray(vec *o, vec *d);
};

#endif /* RAY_H */ 
