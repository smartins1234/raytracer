#include "vec.h"

vec::vec(float xx, float yy, float zz)
{
    x = xx;
    y = yy;
    z = zz;
}

void vec::add(vec *v)
{
    x = x + v->x;
    y = y + v->y;
    z = z + v->z;
}

void vec::subtract(vec *v)
{
    x = x - v->x;
    y = y - v->y;
    z = z - v->z;
}

string vec::toString()
{
    int a = x * 255;
    int b = y * 255;
    int c = z * 255;

    string val = to_string(a) + " " + to_string(b) + " " + to_string(c) + " ";
    return val;
}

vec *vec::normalize(vec *v)
{
    float norm = pow(v->x * v->x + v->y * v->y + v->z * v->z, .5);
    v->x /= norm;
    v->y /= norm;
    v->z /= norm;
    return v;
}

vec *vec::cross(vec *a, vec *b)
{
    vec *c = new vec(0, 0, 0);
    c->x = a->y * b->z - a->z * b->y;
    c->y = a->z * b->x - a->x * b->z;
    c->z = a->x * b->y - a->y * b->x;

    return c;
}

float vec::dot(vec *a, vec *b)
{
    return a->x * b->x + a->y * b->y + a->z * b->z;
}