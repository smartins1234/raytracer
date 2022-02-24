//#include "raytracer.h"
/*#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <typeinfo>

#include "returnInfo.h"
#include "scene.h"
#include "vec.h"*/
#include "raytracer.h"

using namespace std;

vec *getDirection(int i, int j, camera *cam, int imageSize)
{
    float uv_max = cam->lookFrom->z * tan(cam->fov);
    float uv_min = -uv_max;

    float u = i * ((uv_max - uv_min) / imageSize) + uv_min;
    float v = j * ((uv_max - uv_min) / imageSize) + uv_min;

    vec *s = new vec(u, v, 0);
    s->subtract(cam->lookFrom);

    float norm = pow(s->x * s->x + s->y * s->y + s->z * s->z, .5);
    if (norm != 0)
    {
        s->x = s->x / norm;
        s->y = s->y / norm;
        s->z = s->z / norm;
    }
    return s;
}

bool printToFile(ofstream &stream, string &s)
{
    if (stream.is_open())
    {
        stream << s;
    }
    return stream.is_open();
}

bool inShadow(returnInfo *info, int index, vec *lightDirection, vector<shape *> shapes)
{
    vec *point = new vec(info->point->x, info->point->y, info->point->z);
    vec *normal = new vec(info->normal->x, info->normal->y, info->normal->z);
    if(lightDirection == NULL){
        cout << "you have no respect for knights >:'(" << endl;
    }
    vec *direction = new vec(lightDirection->x, lightDirection->y, lightDirection->z);

    point->x += normal->x * .01;                //moving intersected point along normal to avoid problems later
    point->y += normal->y * .01;
    point->z += normal->z * .01;

    ray *r = new ray(point, direction);         //create shadow ray

    for (int k = 0; k < shapes.size(); k++)
    {
        if (k != index)
        {
            shape *current = shapes.at(k);
            returnInfo *info = current->hitShape(r, false); //see if ray hits anyting

            if (info)                                       //if it hits anyting at all, the point's in shadow
            {
                return true;
            }

        }
    }

    return false;
}

vec *calc_color(returnInfo *info, int index, int depth, int maxDepth, vec *lookFrom, light *lgt, vector<shape *> shapes)
{

    float kd = info->color->kd;
    float ks = info->color->ks;
    float ka = info->color->ka;
    float kr = info->color->kr;
    int kgls = info->color->kgls;
    vec *od = info->color->od;
    vec *os = info->color->os;
    vec *normal = info->normal;
    vec *point = info->point;

    vec* total;

    vec *ambient = new vec(od->x * ka * 255, od->y * ka * 255, od->z * ka * 255);   //calculate ambient factor of color

    if( inShadow(info, index, lgt->lightDirection, shapes) ){
        total = new vec(ambient->x, ambient->y, ambient->z);                        //if the objects in shadow, use only ambient color for now
    }
    else
    {
        vec *diffuse;                                                               //calculating the diffuse component
        float angle = normal->dot(normal, lgt->lightDirection);
        if (angle <= 0)
        {
            diffuse = new vec(0, 0, 0);
        }
        else
        {
            float r = kd * lgt->lightColor->x * od->x * angle * 255;
            float g = kd * lgt->lightColor->y * od->y * angle * 255;
            float b = kd * lgt->lightColor->z * od->z * angle * 255;
            diffuse = new vec(r, g, b);
        }

        return diffuse;

        vec *specular;                                                              //calculating the specular component
        vec *reflection = new vec(2 * angle * normal->x, 2 * angle * normal->y, 2 * angle * normal->z);
        reflection->subtract(lgt->lightDirection);
        reflection = reflection->normalize(reflection);

        vec *view = new vec(lookFrom->x, lookFrom->y, lookFrom->z);
        view->subtract(point);
        view = view->normalize(view);

        float spec_angle = view->dot(view, reflection);
        if (spec_angle <= 0)
        {
            specular = new vec(0, 0, 0);
        }
        else
        {
            float r = ks * lgt->lightColor->x * os->x * pow(spec_angle, kgls) * 255;
            float g = ks * lgt->lightColor->y * os->y * pow(spec_angle, kgls) * 255;
            float b = ks * lgt->lightColor->z * os->z * pow(spec_angle, kgls) * 255;

            specular = new vec(r, g, b);
        }

        total = new vec(ambient->x, ambient->y, ambient->z);                        //total color is all 3 components together
        total->add(diffuse);
        total->add(specular);

        if (total->x > 255)                                                         //clip values to 255
            total->x = 255;
        if (total->y > 255)
            total->y = 255;
        if (total->z > 255)
            total->z = 255;
    }

    if(kr > 0 && depth < maxDepth){                                 //if the object is reflective
 
        depth++;                                                    //keeping track of recursion
        ray* r = new ray(point, normal);

        vector<returnInfo *> hits;
        vector<int> indexes;

        for(int k = 0; k < shapes.size(); k++){
            
            returnInfo* info = shapes.at(k)->hitShape(r, false);    //send out secondary ray

            if (info){
                    hits.push_back(info);
                    indexes.push_back(k);
            }
        }

        if(hits.size() > 0){                                        //if the secondary ray hit anything
            
            vector<float> z_vals;                                   //find the closest object
            for (int q = 0; q < hits.size(); q++)
            {
                z_vals.push_back(hits.at(q)->point->z);
            }

            float max = -10;
            int ind = -1;
            for (int w = 0; w < z_vals.size(); w++)
            {
                if (z_vals.at(w) > max)
                {
                    max = z_vals.at(w);
                    ind = w;
                }
            }

            returnInfo* dup = hits.at(ind)->copy();


            vec* ref_color = calc_color(dup, ind, depth, maxDepth, lookFrom, lgt, shapes);           //calculate color at secondary intersection

            ref_color->x *= kr;                                     //include reflected color into final color
            ref_color->y *= kr;
            ref_color->z *= kr;

            total->x *= (1 - kr);
            total->y *= (1 - kr);
            total->z *= (1 - kr);

            total->add(ref_color);
        }
    }

    return total;
}

void render(scene *myScene, string filepath)
{
    ofstream myfile(filepath);
    if (!myfile.is_open())
    {
        cout << "Couldn't open file" << endl;
        return;
    }
    myfile << "P3\n";
    myfile << myScene->imageSize << " " << myScene->imageSize << "\n";
    myfile << "255\n";

    for (int i = myScene->imageSize; i > 0; i--)
    {
        for (int j = 0; j < myScene->imageSize; j++)
        {
            vec *dir = getDirection(j, i, myScene->cam, myScene->imageSize);      //calculate the direction of the ray
            ray *r = new ray(myScene->cam->lookFrom, dir);

            string miss = myScene->bgColor->toString();          //background color
            vector<returnInfo *> hits;          //info of each object hit by the ray
            vector<int> indexes;                //indexes of objects hit by the ray

            for (int k = 0; k < myScene->shapes.size(); k++)                 //for each object
            {
                shape *current = myScene->shapes.at(k);
                returnInfo *info = current->hitShape(r, true);      //see if the ray hits the object

                if (info)                                           //if it does, add it to the list
                {
                    hits.push_back(info);
                    indexes.push_back(k);
                }
            }

            if (hits.size() == 0)           //if no objects were hit, print the bg color
            {
                printToFile(myfile, miss);
            }
            
            else if (hits.size() > 0)
            {
                vector<float> z_vals;                           //get the z-values for each hit object
                for (int q = 0; q < hits.size(); q++)
                {
                    z_vals.push_back(hits.at(q)->point->z);
                }

                float max = -10;
                int index = -1;
                for (int w = 0; w < z_vals.size(); w++)         //get the index of object with highest z value
                {
                    if (z_vals.at(w) > max)
                    {
                        max = z_vals.at(w);
                        index = w;
                    }
                }

                vec *total_color = calc_color(hits.at(index), indexes.at(index), 0, myScene->maxDepth, myScene->cam->lookFrom, myScene->lights.front(), myScene->shapes);    //calculate the color at this pixel
                
                string color = to_string((int)total_color->x) + " " + to_string((int)total_color->y) + " " + to_string((int)total_color->z) + " ";
                printToFile(myfile, color);
            }
        }
        string enter = "\n";
        printToFile(myfile, enter);
    }

    myfile.close();
}