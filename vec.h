#ifndef VEC_H
#define VEC_H

#include <string>
#include <cmath>

using namespace std;

class vec
{

public:
    float x;
    float y;
    float z;

    vec(float xx, float yy, float zz);

    void add(vec *v);

    void subtract(vec *v);

    string toString();

    vec* normalize(vec *v);

    vec* cross(vec *a, vec *b);

    float dot(vec *a, vec *b);

};

#endif /* VEC_H */ 
