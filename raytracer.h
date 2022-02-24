#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <typeinfo>

#include "returnInfo.h"
#include "scene.h"
#include "vec.h"

using namespace std;

vec *getDirection(int i, int j, camera *cam, int imageSize);

bool printToFile(ofstream &stream, string &s);

bool inShadow(returnInfo *info, int index, vec *lightDirection, vector<shape *> shapes);

vec *calc_color(returnInfo *info, int index, int depth, int maxDepth, vec *lookFrom, light *lgt, vector<shape *> shapes);

void render(scene *myScene, string filepath);

#endif /* RAYTRACER_H */ 
