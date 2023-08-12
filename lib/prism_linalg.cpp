#include <prism_linalg.h>

double dot(Vertex *a, Vertex *b) {
    return a->x*b->x+a->y*b->y+a->z*b->z;
}

Vertex cross(Vertex *a, Vertex *b) {
    Vertex v(a->y*b->z-a->z*b->y,a->z*b->x-a->x*b->z,a->x*b->y-a->y*b->x);
    return v;
}

double dist_line_point(Vertex *line, Vertex *point) {
    Vertex APxd = cross(point,line);
    double APxdL = sqrt(dot(&APxd,&APxd));
    double dL = sqrt(dot(line,line));
    return APxdL/dL;
}