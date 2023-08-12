#ifndef __prism_linalg_h
#define __prism_linalg_h

#include <prism_models.h>

double dot(Vertex *a, Vertex *b);

Vertex cross(Vertex *a, Vertex *b);

double dist_line_point(Vertex *line, Vertex *point);

#endif