#ifndef SHADER_H
#define SHADER_H

#include "vec.h"

using namespace std;

class shader
{
public:
    float kd;
    float ks;
    float ka;
    vec *od;
    vec *os;
    int kgls;
    float kr;

    shader(float a, float b, float c, vec *d, vec *e, int f, float g);
};

#endif /* SHADER_H */ 
