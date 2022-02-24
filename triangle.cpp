#include "triangle.h"

using namespace std;

triangle::triangle(vec *u, vec *v, vec *n, shader *col)
{
    a = u;
    b = v;
    c = n;
    color = col;
}

vec* triangle::getNorm()
{
    vec *one = new vec(b->x - a->x, b->y - a->y, b->z - a->z);
    vec *two = new vec(c->x - a->x, c->y - a->y, c->z - a->z);

    return one->cross(one, two);
}

bool triangle::inPoly(vec *point, vec *norm)
{
    float aTest = abs(norm->x);
    float bTest = abs(norm->y);
    float cTest = abs(norm->z);
    vec2 *tri_a;
    vec2 *tri_b;
    vec2 *tri_c;
    vec2 *inter;

    if (aTest >= bTest && aTest >= cTest)       //find the largest component of the normal vector and remove it from all points
    {
        tri_a = new vec2(a->y, a->z);
        tri_b = new vec2(b->y, b->z);
        tri_c = new vec2(c->y, c->z);
        inter = new vec2(point->y, point->z);
    }
    else if (bTest >= aTest && bTest >= cTest)
    {
        tri_a = new vec2(a->x, a->z);
        tri_b = new vec2(b->x, b->z);
        tri_c = new vec2(c->x, c->z);
        inter = new vec2(point->x, point->z);
    }
    else
    {
        tri_a = new vec2(a->x, a->y);
        tri_b = new vec2(b->x, b->y);
        tri_c = new vec2(c->x, c->y);
        inter = new vec2(point->x, point->y);
    }

    tri_a->x -= inter->x;                       //translate intersection point to the origin
    tri_a->y -= inter->y;
    tri_b->x -= inter->x;
    tri_b->y -= inter->y;
    tri_c->x -= inter->x;
    tri_c->y -= inter->y;

    vector<vec2 *> points;                      //putting points in vector for convenience
    points.push_back(tri_a);
    points.push_back(tri_b);
    points.push_back(tri_c);

    int numCrossings = 0;                       //number of times crossed the positive x-axis
    int sign;                                   //current y value sign
    int nextSign;                               //next y value sign
    if (tri_a->y < 0)
        sign = -1;
    else
        sign = 1;
    for (int i = 0; i < points.size(); i++)
    {
        vec2 *first = points.at(i);
        vec2 *second;
        if (i < (points.size() - 1))
        {
            second = points.at(i + 1);
        }
        else
        {
            second = points.at(0);              //loop back around to first point
        }

        if (second->y < 0)                      //find nextSign
            nextSign = -1;
        else
            nextSign = 1;

        if (sign != nextSign)                   //if they're not the same
        {
            if (first->x > 0 && second->x > 0)  //if both x vals are positive, definitely crossed the axis
            {
                numCrossings++;
            }
            else if (first->x > 0 || second->x > 0) //if at least one is positive, maybe crossed the axis
            {
                float uCross = first->x - (first->y * (second->x - first->x) / (second->y - first->y));
                if (uCross > 0)                 //if x intercept of the line is positive, crossed the positive x axis
                {
                    numCrossings++;
                }
            }
        }

        sign = nextSign;
    }

    if (numCrossings % 2 == 1)      //odd numCrossings means the point is inside the triangle
        return true;
    else
        return false;
}

returnInfo* triangle::hitShape(ray *r, bool prim)
{
    vec *normal = getNorm();
    float n = pow(normal->x * normal->x + normal->y * normal->y + normal->z * normal->z, .5);
    normal->x = normal->x / n;
    normal->y = normal->y / n;
    normal->z = normal->z / n;                  //calculate and normalize the normal of plane

    vec *v = new vec(-a->x, -a->y, -a->z);
    float d = v->dot(v, normal);                   //find distance from plane to the origin

    float test = normal->dot(normal, r->direction);     //check if plane is visible
    if (test == 0)
        return NULL;
    else if(test > 0 && prim)
        return NULL;


    float t = normal->dot(normal, r->origin);
    t += d;
    t *= -1;
    t /= test;                                  //calculate time t

    if (t <= 0)                                 //intersection is behind camera
        return NULL;

    r->direction->x = r->direction->x * t;      //calculating interection point
    r->direction->y = r->direction->y * t;
    r->direction->z = r->direction->z * t;

    vec *p = new vec(r->direction->x + r->origin->x, r->direction->y + r->origin->y, r->direction->z + r->origin->z);
    if (inPoly(p, normal))                      //check if intersection is within the triangle
    {
        return new returnInfo(p, normal, color);
    }
    return NULL;
}