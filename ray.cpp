#include "ray.h"

using namespace std;

ray::ray(vec *o, vec *d)
{
    origin = o;
    direction = d;
}