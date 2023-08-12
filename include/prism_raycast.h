#ifndef __prism_raycast_h
#define __prism_raycast_h

#include <prism_models.h>
#include <prism_linalg.h>
#include <prism_config.h>

class RayCast {
private:
    double sensw = 36.0;
    double sensh = 36.0/WIDTH*HEIGHT;
    long int objfacomt = 0;
    long int facfacomt = 0;
    Vertex lightD = Vertex(10,0,10);
    double lightL = sqrt(dot(&lightD,&lightD));
    Vertex lightU = Vertex(lightD.x/lightL,lightD.y/lightL,lightD.z/lightL);
    double lightW = 0.68, ambientW = 0.32;
public:
    RayCast(Scene *scene, unsigned char *img, double *zbuf);
};

#endif