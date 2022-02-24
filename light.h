#ifndef LIGHT_H
#define LIGHT_H

#include "vec.h"

using namespace std;

class light{
public:
    vec *lightColor;
    vec *lightDirection;

    //functions
    vec *getDir();
};

#endif /* LIGHT_H */ 
