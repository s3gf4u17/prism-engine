#include <prism_models.h>

Vertex::Vertex(double x, double y, double z) {
    this->x = x; this->y = y; this->z = z;
}

Vertex::Vertex() {
    this->x = 0; this->y = 0; this->z = 0;
}

Camera::Camera(Vertex pos, Vertex rot) {
    this->pos = pos;
    this->rot = rot;
}

Face::Face(Vertex a, Vertex b, Vertex c, Vertex n, Vertex nb, Vertex nc) {
    this->a = a; this->b = b; this->c = c; this->n = n; this->nb = nb; this->nc = nc;
}

Object::Object(std::vector<Face> faces) {
    this->faces.swap(faces);
}

Object::Object() {

}

Material::Material(unsigned char R, unsigned char G, unsigned char B) {
    this->R = R; this->G = G; this->B = B;
}

Scene::Scene(std::string source, Camera *camera) {
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
                    int n1 = stoi(parts[1].substr(n1s,n1e-n1s))-1;

                    int v2s = 0; int v2e = parts[i+1].find("/",0);
                    int t2s = v2e+1; int t2e = parts[i+1].find("/",t2s);
                    int n2s = t2e+1; int n2e = parts[i+1].find("/",n2s);
                    int n2 = stoi(parts[i+1].substr(n2s,n2e-n2s))-1;

                    int v3s = 0; int v3e = parts[i+2].find("/",0);
                    int t3s = v3e+1; int t3e = parts[i+2].find("/",t3s);
                    int n3s = t3e+1; int n3e = parts[i+2].find("/",n3s);
                    int n3 = stoi(parts[i+2].substr(n3s,n3e-n3s))-1;

                    int v1 = stoi(parts[1].substr(0,parts[1].find("/",0)))-1;
                    int v2 = stoi(parts[i+1].substr(0,parts[i+1].find("/",0)))-1;
                    int v3 = stoi(parts[i+2].substr(0,parts[i+2].find("/",0)))-1;
                    Face face(vertices[v1],vertices[v2],vertices[v3],normals[n1],normals[n2],normals[n3]);
                    auto mat = materials.find(cmat);
                    face.R = mat->second.R;
                    face.G = mat->second.G;
                    face.B = mat->second.B;
                    faces.push_back(face);
                }
            } else if (parts[0]=="vn") {
                double x0 = stod(parts[1]);
                double y0 = stod(parts[2]);
                double z0 = stod(parts[3]);
                double x1 = cos(-camera->rot.z/180.0*M_PI)*x0-sin(-camera->rot.z/180.0*M_PI)*y0;
                double y1 = sin(-camera->rot.z/180.0*M_PI)*x0+cos(-camera->rot.z/180.0*M_PI)*y0;
                double x2 = cos(-camera->rot.y/180.0*M_PI)*x1-sin(-camera->rot.y/180.0*M_PI)*z0;
                double z2 = sin(-camera->rot.y/180.0*M_PI)*x1+cos(-camera->rot.y/180.0*M_PI)*z0;
                double y3 = cos(-camera->rot.x/180.0*M_PI)*y1-sin(-camera->rot.x/180.0*M_PI)*z2;
                double z3 = sin(-camera->rot.x/180.0*M_PI)*y1+cos(-camera->rot.x/180.0*M_PI)*z2;
                Vertex n(x2,y3,z3);
                normals.push_back(n);
            } else if (parts[0]=="mtllib") {
                std::string matsrc = "test/" + parts[1];
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