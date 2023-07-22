#pragma once

#include <math.h>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

class Vertex {
public:
    double x,y,z;
};

class Face {
public:
    Vertex* a,b,c,n,bbxc;
    double bbxr;
};

class Object {
public:
    std::vector<Face*> faces;
    Vertex bbxc;
    double bbxr;
};

struct Vertex {
    double x;
    double y;
    double z;
};

struct Face {
    Vertex a;
    Vertex b;
    Vertex c;
    Vertex n;
    Vertex sc; // sphere center
    double sr; // sphere radius
};

struct Object {
    std::string name;
    std::vector<Face> faces;
    Vertex sc; // sphere center
    double sr; // sphere radius
};

class Scene {
private:
    Object o;
public:
    std::vector<Vertex> vertices;
    std::vector<Vertex> normals;
    std::vector<Object> objects;
    Scene(std::string source) {
        std::fstream file(source);
        std::string buffer;
        while(file.is_open()&&getline(file,buffer)) {
            std::vector<std::string> parts;
            int front=0,back=0;
            while (true) {
                front=buffer.find(" ",back);
                parts.push_back(buffer.substr(back,front-back));
                if (front==std::string::npos) break;
                back = front + 1;
            }
            if (parts[0]=="mtllib") {
                // read mtl file
            } else if (parts[0]=="o") {
                if (!o.name.empty()) objects.push_back(o);
                o.name = parts[1];
                o.faces.clear();
            } else if (parts[0]=="v") {
                Vertex v{stod(parts[1]),stod(parts[2]),stod(parts[3])};
                vertices.push_back(v);
            } else if (parts[0]=="vn") {
                Vertex n{stod(parts[1]),stod(parts[2]),stod(parts[3])};
                normals.push_back(n);
            } else if (parts[0]=="usemtl") {
                // swap material
            } else if (parts[0]=="f") {
                for (int i = 1; i < parts.size()-1 ; i++) {
                    int v1 = stoi(parts[1].substr(0,parts[1].find("/",0)))-1;
                    int v2 = stoi(parts[i].substr(0,parts[i].find("/",0)))-1;
                    int v3 = stoi(parts[i+1].substr(0,parts[i+1].find("/",0)))-1;
                    Face f{vertices[v1],vertices[v2],vertices[v3]};
                    o.faces.push_back(f);
                }
            }
        }
        if (!o.name.empty()) objects.push_back(o);
        for (Object object : objects) {
            Vertex avg{0.0,0.0,0.0};
            int count = 0;
            for (Face face : object.faces) {
                face.sc.x = (face.a.x+face.b.x+face.c.x)/3.0;
                face.sc.y = (face.a.y+face.b.y+face.c.y)/3.0;
                face.sc.z = (face.a.z+face.b.z+face.c.z)/3.0;
                double dista = sqrt(pow(face.a.x-face.sc.x,2)+pow(face.a.y-face.sc.y,2)+pow(face.a.z-face.sc.z,2));
                double distb = sqrt(pow(face.b.x-face.sc.x,2)+pow(face.b.y-face.sc.y,2)+pow(face.b.z-face.sc.z,2));
                double distc = sqrt(pow(face.c.x-face.sc.x,2)+pow(face.c.y-face.sc.y,2)+pow(face.c.z-face.sc.z,2));
                face.sr = std::max(std::max(dista,distb),distc);
                avg.x += (face.a.x-avg.x)/(count+1.0);
                avg.x += (face.b.x-avg.x)/(count+2.0);
                avg.x += (face.c.x-avg.x)/(count+3.0);
                avg.y += (face.a.y-avg.y)/(count+1.0);
                avg.y += (face.b.y-avg.y)/(count+2.0);
                avg.y += (face.c.y-avg.y)/(count+3.0);
                avg.z += (face.a.z-avg.z)/(count+1.0);
                avg.z += (face.b.z-avg.z)/(count+2.0);
                avg.z += (face.c.z-avg.z)/(count+3.0);
                count+=3;
            }
            object.sc.x = avg.x;
            std::cout << object.sc.x << std::endl;
        }
    }
    friend std::ostream& operator <<(std::ostream& os, Scene *scene) {
        os << "vrt cnt: " << scene->vertices.size() << std::endl;
        os << "obj cnt: " << scene->objects.size() << " " << scene->objects[1].sc.y;
        return os;
    }
};