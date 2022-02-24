#ifndef RETURNINFO_H
#define RETURNINFO_H

#include "shader.h"

using namespace std;

class returnInfo
{
public:
    vec *point;
    vec *normal;
    shader *color;

    returnInfo(vec *p, vec *n, shader *c);

    returnInfo* copy();
};

#endif /* RETURNINFO_H */ 
