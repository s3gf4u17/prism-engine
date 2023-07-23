class Vertex {
public:
    double x,y,z;
    Vertex(double x, double y, double z) {
        this->x = x; this->y = y; this->z = z;
    }
    Vertex() {
        this->x = 0; this->y = 0; this->z = 0;
    }
};

double dot(Vertex a, Vertex b) {
    return a.x*b.x+a.y*b.y+a.z*b.z;
}

Vertex cross(Vertex a, Vertex b) {
    Vertex v(a.y*b.z-a.z*b.y,a.z*b.x-a.x*b.z,a.x*b.y-a.y*b.x);
    return v;
}

class Camera {
public:
    Vertex pos,rot;
    Camera(Vertex pos, Vertex rot) {
        this->pos = pos;
        this->rot = rot;
    }
};

class Face {
public:
    Vertex a,b,c,n,sphc;
    double sphr;
    Face(Vertex a, Vertex b, Vertex c, Vertex n) {
        this->a = a; this->b = b; this->c = c; this->n = n;
        this->sphc = Vertex((a.x+b.x+c.x)/3.0,(a.y+b.y+c.y)/3.0,(a.z+b.z+c.z)/3.0);
        this->sphr = std::max(sqrt(dot(a,sphc)),std::max(sqrt(dot(b,sphc)),sqrt(dot(c,sphc))));
    }
};

class Object {
public:
    std::vector<Face> faces;
    Vertex sphc;
    double sphr = 0.0;
    double sumx,sumy,sumz;
    int count;
    Object(std::vector<Face> faces) {
        this->faces.swap(faces);
        sumx=0;sumy=0;sumz=0;count=0;
    }
    Object() {}
    void find_origin() {
        for (int i = 0 ; i < faces.size() ; i++) {
            sumx+=faces[i].a.x;sumx+=faces[i].b.x;sumx+=faces[i].c.x;
            sumy+=faces[i].a.y;sumy+=faces[i].b.y;sumy+=faces[i].c.y;
            sumz+=faces[i].a.z;sumz+=faces[i].b.z;sumz+=faces[i].c.z;
            count+=3;
        }
        sphc = Vertex(sumx/count,sumy/count,sumz/count);
        for (Face face : faces) {
            sphr = std::max(sphr,sqrt(pow(face.a.x-sphc.x,2)+pow(face.a.y-sphc.y,2)+pow(face.a.z-sphc.z,2)));
            sphr = std::max(sphr,sqrt(pow(face.b.x-sphc.x,2)+pow(face.b.y-sphc.y,2)+pow(face.b.z-sphc.z,2)));
            sphr = std::max(sphr,sqrt(pow(face.c.x-sphc.x,2)+pow(face.c.y-sphc.y,2)+pow(face.c.z-sphc.z,2)));
        }
    }
};

class Scene {
private:
    std::vector<Vertex> vertices;
    std::vector<Vertex> normals;
    std::vector<Face> faces;
    Object object;
public:
    std::vector<Object> objects;
    Scene(std::string source, Camera *camera) {
        std::fstream file(source);
        std::string buffer;
        while(file.is_open()&&getline(file,buffer)) {
            std::vector<std::string> parts;
            int front = 0, back = 0;
            while (true) {
                front = buffer.find(" ",back);
                parts.push_back(buffer.substr(back,front-back));
                if (front==std::string::npos) break;
                back = front + 1;
            }
            if (parts[0]=="o") {
                if (!faces.empty()) {
                    Object object(faces);
                    object.find_origin();
                    objects.push_back(object);
                    faces.clear();
                }
            } else if (parts[0]=="v") {
                double x0 = stod(parts[1])-camera->pos.x;
                double y0 = stod(parts[2])-camera->pos.y;
                double z0 = stod(parts[3])-camera->pos.z;
                double x1 = cos(-camera->rot.z/180.0*M_PI)*x0-sin(-camera->rot.z/180.0*M_PI)*y0;
                double y1 = sin(-camera->rot.z/180.0*M_PI)*x0+cos(-camera->rot.z/180.0*M_PI)*y0;
                double x2 = cos(-camera->rot.y/180.0*M_PI)*x1-sin(-camera->rot.y/180.0*M_PI)*z0;
                double z2 = sin(-camera->rot.y/180.0*M_PI)*x1+cos(-camera->rot.y/180.0*M_PI)*z0;
                double y3 = cos(-camera->rot.x/180.0*M_PI)*y1-sin(-camera->rot.x/180.0*M_PI)*z2;
                double z3 = sin(-camera->rot.x/180.0*M_PI)*y1+cos(-camera->rot.x/180.0*M_PI)*z2;
                Vertex v(x2,y3,z3);
                vertices.push_back(v);
            } else if (parts[0]=="f") {
                for (int i = 1 ; i < parts.size()-2 ; i++) {
                    int v1s = 0; int v1e = parts[1].find("/",0);
                    int t1s = v1e+1; int t1e = parts[1].find("/",t1s);
                    int n1s = t1e+1; int n1e = parts[1].find("/",n1s);
                    int n = stoi(parts[1].substr(n1s,n1e-n1s))-1;
                    int v1 = stoi(parts[1].substr(0,parts[1].find("/",0)))-1;
                    int v2 = stoi(parts[i+1].substr(0,parts[i].find("/",0)))-1;
                    int v3 = stoi(parts[i+2].substr(0,parts[i+1].find("/",0)))-1;
                    Face face(vertices[v1],vertices[v2],vertices[v3],normals[n]);
                    faces.push_back(face);
                }
            } else if (parts[0]=="vn") {
                Vertex n(stod(parts[1]),stod(parts[2]),stod(parts[3]));
                normals.push_back(n);
            }
        }
        if (!faces.empty()) {
            Object object(faces);
            object.find_origin();
            objects.push_back(object);
            faces.clear();
        }
    }
    friend std::ostream& operator <<(std::ostream& os, Scene *scene) {
        os << "vrtcnt\t" << scene->vertices.size() << std::endl;
        os << "objcnt\t" << scene->objects.size() << std::endl;
        for (Object object : scene->objects) {
            os << "obj origin(" << object.sphc.x << "," << object.sphc.y << "," << object.sphc.z << ")";
            os << " radius(" << object.sphr << ")" << std::endl;
        }
        return os;
    }
};