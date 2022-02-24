#ifndef DIR_LIGHT_H
#define DIR_LIGHT_H

#include "light.h"
#include "vec.h"

using namespace std;

class dirLight : public light
{
public:
    vec *lightDirection;

    dirLight(vec *color, vec *dir);
};

#endif /* DIR_LIGHT_H */ 
