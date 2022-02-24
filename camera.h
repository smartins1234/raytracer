#ifndef CAMERA_H
#define CAMERA_H

#include "vec.h"

using namespace std;

class camera{
public:
    vec *lookFrom;
    vec *lookAt;
//    float fov_deg;
    float fov;

    camera(vec *from, vec *at, float deg);
};

#endif /* CAMERA_H */
