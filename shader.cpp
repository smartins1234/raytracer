#include "shader.h"

using namespace std;

shader::shader(float a, float b, float c, vec *d, vec *e, int f, float g)
{
    kd = a;
    ks = b;
    ka = c;
    od = d;
    os = e;
    kgls = f;
    kr = g;
}