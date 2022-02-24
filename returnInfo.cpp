#include "returnInfo.h"

using namespace std;

returnInfo::returnInfo(vec *p, vec *n, shader *c)
{
    point = p;
    normal = n;
    color = c;
}

returnInfo* returnInfo::copy(){
    vec* p = new vec(point->x, point->y, point->z);
    vec* n = new vec(normal->x, normal->y, normal->z);
    vec* od = new vec(color->od->x, color->od->y, color->od->z);
    vec* os = new vec(color->os->x, color->os->y, color->os->z);
    shader* c = new shader(color->kd, color->ks, color->ka, od, os, color->kgls, color->kr);
    return new returnInfo(p, n, c);
}