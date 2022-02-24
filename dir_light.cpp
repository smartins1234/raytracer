#include "dir_light.h"

using namespace std;

dirLight::dirLight(vec *color, vec *dir){
    lightColor = color;
    lightDirection = dir;
}