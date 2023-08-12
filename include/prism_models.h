#ifndef __prism__objects_h
#define __prism__objects_h

#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <math.h>

class Vertex {
public:
    double x,y,z;
    Vertex(double x, double y, double z);
    Vertex();
};

class Camera {
public:
    Vertex pos,rot;
    Camera(Vertex pos, Vertex rot);
};

class Face {
public:
    Vertex a,b,c,n;
    unsigned char R,G,B;
    Face(Vertex a, Vertex b, Vertex c, Vertex n);
};

class Object {
public:
    std::vector<Face> faces;
    Object(std::vector<Face> faces);
    Object();
};

class Material {
public:
    std::string name;
    unsigned char R,G,B;
    Material(unsigned char R, unsigned char G, unsigned char B);
};

class Scene {
private:
    std::vector<Vertex> vertices;
    std::vector<Vertex> normals;
    std::vector<Face> faces;
    std::map<std::string,Material> materials;
    Object object;
    std::string cmat = "Material";
    Material material = Material(0,0,0);
public:
    std::vector<Object> objects;
    Scene(std::string source, Camera *camera);
};

#endif