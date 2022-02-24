#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <typeinfo>
#include "raytracer.h"
#include "dir_light.h"
#include "sphere.h"
#include "triangle.h"
#include "vec.h"

using namespace std;

int main()
{
    //define scene first
    int imageSize = 850;
    int maxDepth = 10;

    vec *bgColor = new vec(.2, .2, .2);

    vec *lookFrom = new vec(0, 0, 1);
    vec *lookAt = new vec(0, 0, 0);
    float fov_deg = 28;
    camera *cam = new camera(lookFrom, lookAt, fov_deg);

    vec *lightColor = new vec(1, 1, 1);
    vec *lightDirection = new vec(1, 0, 0);
    dirLight *dir = new dirLight(lightColor, lightDirection);
    vector<dirLight *> lights;
    cout << lightDirection->toString() << endl;
    lights.push_back(dir);

    if (lights.front()->getDir() == NULL){
        cout << "ARRRRGGGG" << endl;
        return 1;
    }

    shader *c1 = new shader(0.6, 0.3, 0.1, new vec(1, 1, 1), new vec(1, 1, 1), 4, 0);
    shader *c2 = new shader(0.6, 0.3, 0.1, new vec(1, 0, 0), new vec(1, 1, 1), 32, 0);
    shader *c3 = new shader(0.6, 0.3, 0.1, new vec(0, 1, 0), new vec(1, 1, 1), 32, 0);
    shader *c4 = new shader(0.6, 0.3, 0.1, new vec(0, 0, 1), new vec(1, 1, 1), 32, 0);
    shader *c5 = new shader(0.9, 0, 0.1, new vec(1, 1, 0), new vec(1, 1, 1), 4, 0);

    sphere *s1 = new sphere(new vec(.35, 0, -.1), .05, c1);
    sphere *s2 = new sphere(new vec(.2, 0, -.1), .075, c2);
    sphere *s3 = new sphere(new vec(-.6, 0, 0), .3, c3);
    triangle *t1 = new triangle(new vec(0.3, -0.3, -0.4), new vec(0, 0.3, -0.1), new vec(-0.3, -0.3, 0.2), c4);
    triangle *t2 = new triangle(new vec(-.2, .1, .1), new vec(-.2, -.5, .2), new vec(-.2, .1, -.3), c5);

    vector<shape*> shapes{
        s1, s2, s3, t1, t2
    };

    scene *myScene = new scene(imageSize, maxDepth, shapes, lights, cam, bgColor);

    string filepath = "output.ppm";

    render(myScene, filepath);

    return 0;
}