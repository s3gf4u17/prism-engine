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

double dot(Vertex *a, Vertex *b) {
    return a->x*b->x+a->y*b->y+a->z*b->z;
}

Vertex cross(Vertex *a, Vertex *b) {
    Vertex v(a->y*b->z-a->z*b->y,a->z*b->x-a->x*b->z,a->x*b->y-a->y*b->x);
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
    Vertex a,b,c,n;
    unsigned char R,G,B;
    Face(Vertex a, Vertex b, Vertex c, Vertex n) {
        this->a = a; this->b = b; this->c = c; this->n = n;
    }
};

class Object {
public:
    std::vector<Face> faces;
    Object(std::vector<Face> faces) {
        this->faces.swap(faces);
    }
    Object() {}
};

class Material {
public:
    std::string name;
    unsigned char R,G,B;
    Material(unsigned char R, unsigned char G, unsigned char B) {
        this->R = R; this->G = G; this->B = B;
    } 
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
                    int v2 = stoi(parts[i+1].substr(0,parts[i+1].find("/",0)))-1;
                    int v3 = stoi(parts[i+2].substr(0,parts[i+2].find("/",0)))-1;
                    Face face(vertices[v1],vertices[v2],vertices[v3],normals[n]);
                    auto mat = materials.find(cmat);
                    face.R = mat->second.R;
                    face.G = mat->second.G;
                    face.B = mat->second.B;
                    faces.push_back(face);
                }
            } else if (parts[0]=="vn") {
                Vertex n(stod(parts[1]),stod(parts[2]),stod(parts[3]));
                normals.push_back(n);
            } else if (parts[0]=="mtllib") {
                std::string matsrc = "model/" + parts[1];
                std::fstream matf(matsrc);
                while(matf.is_open()&&getline(matf,buffer)) {
                    std::vector<std::string> matparts;
                    int mfront = 0, mback = 0;
                    while (true) {
                        mfront = buffer.find(" ",mback);
                        matparts.push_back(buffer.substr(mback,mfront-mback));
                        if (mfront==std::string::npos) break;
                        mback = mfront + 1;
                    }
                    if (matparts[0]=="newmtl") {
                        if (material.name!="") materials.insert({material.name,material});
                        material = Material(0,0,0);
                        material.name = matparts[1];
                    } else if (matparts[0]=="Kd") {
                        material.R = (unsigned char)(stod(matparts[1])*255);
                        material.G = (unsigned char)(stod(matparts[2])*255);
                        material.B = (unsigned char)(stod(matparts[3])*255);
                    }
                }
                if (material.name!="") materials.insert({material.name,material});
            } else if (parts[0]=="usemtl") {
                cmat = parts[1];
            }
        }
        if (!faces.empty()) {
            Object object(faces);
            objects.push_back(object);
            faces.clear();
        }
    }
    friend std::ostream& operator <<(std::ostream& os, Scene *scene) {
        os << "vrtcnt\t" << scene->vertices.size() << std::endl;
        os << "objcnt\t" << scene->objects.size() << std::endl;
        return os;
    }
};