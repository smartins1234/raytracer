#include "sphere.h"

using namespace std;

sphere::sphere(vec *c, float r, shader *s)
{
    center = c;
    radius = r;
    color = s;
}

returnInfo* sphere::hitShape(ray *r, bool prim)
{
    vec *d = r->direction;
    vec *o = r->origin;
    vec *c = center;
    float rad = radius;

    //B and C values for the quadratic equation
    float B = 2 * (d->x * o->x - d->x * c->x + d->y * o->y - d->y * c->y + d->z * o->z - d->z * c->z);
    float C = o->x * o->x - 2 * o->x * c->x + c->x * c->x + o->y * o->y - 2 * o->y * c->y + c->y * c->y + o->z * o->z - 2 * o->z * c->z + c->z * c->z - rad * rad;

    //determinant for the quadratic equation
    float D = B * B - 4 * C;

    if (D < 0)
    {
        return NULL;
    }
    else if (D == 0)
    {
        return NULL;
    }
    else
    {
        float t0 = (-B - pow(D, .5)) / 2;

        if (t0 > 0)
        {
            vec *intersect = new vec(o->x + t0 * d->x, o->y + t0 * d->y, o->z + t0 * d->z);
            vec *normal = new vec((intersect->x - c->x), (intersect->y - c->y), (intersect->z - c->z));

            normal->x /= radius;
            normal->y /= radius;
            normal->z /= radius;

            normal = normal->normalize(normal);

            return new returnInfo(intersect, normal, color);
        }
        float t1 = (-B + pow(D, .5)) / 2;

        if (t1 > 0)
        {
            vec *intersect = new vec(o->x + t1 * d->x, o->y + t1 * d->y, o->z + t1 * d->z);
            vec *normal = new vec((intersect->x - c->x) / rad, (intersect->y - c->y) / rad, (intersect->z - c->z) / rad);
            normal = normal->normalize(normal);
            return new returnInfo(intersect, normal, color);
        }
        return NULL;
    }
}