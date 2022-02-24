#include "scene.h"

using namespace std;

scene::scene(int size, int depth, vector<shape *> s, vector<dirLight *> l, camera *c, vec *bg){
    imageSize = size;
    maxDepth = depth;
    shapes = s;
    lights = l;
    cam = c;
    bgColor = bg;
}