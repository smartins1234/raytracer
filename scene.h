#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "shape.h"
#include "camera.h"
#include "dir_light.h"

using namespace std;

class scene
{
public:
    int imageSize;
    int maxDepth;
    vector<shape *> shapes;
    vector<dirLight *> lights;
    camera *cam;
    vec *bgColor;

    scene(int size, int depth, vector<shape *> s, vector<dirLight *> l, camera *c, vec *bg);
};

#endif /* SCENE_H */ 
