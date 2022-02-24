#include "camera.h"

using namespace std;

camera::camera(vec *from, vec *at, float deg){
    lookFrom = from;
    lookAt = at;
    fov = deg * 3.14159265 / 180;
}