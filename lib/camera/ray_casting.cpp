class RayCasting {
private:
    Vertex cameraPos{1.4,1,16};
public:
    RayCasting(ObjFile *of, unsigned char *pixels) {
        Vertex lightPosition{10,-10,18};
        double lightPower = 0.48;
        double ambient = 0.12;
        Vertex lightDirectionN{lightPosition.x-cameraPos.x,lightPosition.y-cameraPos.y,lightPosition.z-cameraPos.z};
        double lightDirectionL = sqrt(dot(&lightDirectionN,&lightDirectionN));
        Vertex lightDirectionU{lightDirectionN.x/lightDirectionL,lightDirectionN.y/lightDirectionL,lightDirectionN.z/lightDirectionL};
        // Moller–Trumbore intersection algorithm - https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm
        for (int y = 0 ; y < HEIGHT ; y++) {
            for (int x = 0 ; x < WIDTH ; x++) {
                Face closeF;
                bool closeB = false;
                double closeD = 10000.0;
                Vertex rayStart = cameraPos;
                double sensorW = 36.0;
                double sensorH = 36.0/WIDTH*HEIGHT;
                Vertex rayDestN{-sensorW/2.0+x*(sensorW/WIDTH)+sensorW/WIDTH/2,sensorH/2.0-y*(sensorH/HEIGHT)-sensorH/HEIGHT/2,-50.0};
                double rayDestL = sqrt(dot(&rayDestN,&rayDestN));
                Vertex rayDestU{rayDestN.x/rayDestL,rayDestN.y/rayDestL,rayDestN.z/rayDestL};
                for (Face face : of->faces) {
                    const float EPSILON = 0.0000001;
                    Vertex edge1{face.b.x-face.a.x,face.b.y-face.a.y,face.b.z-face.a.z};
                    Vertex edge2{face.c.x-face.a.x,face.c.y-face.a.y,face.c.z-face.a.z};
                    Vertex h = cross(&rayDestU,&edge2);
                    double a = dot(&edge1,&h);
                    if (a > -EPSILON && a < EPSILON) continue; // parallel
                    double f = 1.0/a;
                    Vertex s{cameraPos.x-face.a.x,cameraPos.y-face.a.y,cameraPos.z-face.a.z};
                    double u = f * dot(&s,&h);
                    if (u < 0.0 || u > 1.0) continue;
                    Vertex q = cross(&s,&edge1);
                    double v = f * dot(&rayDestU,&q);
                    if (v < 0.0 || u + v > 1.0) continue;
                    double t = f * dot(&edge2,&q);
                    if (t>EPSILON && t<closeD) {
                        closeD = t;
                        closeB = true;
                        closeF = face;
                    }
                }
                if (closeB) {
                    double diff = std::max(dot(&(closeF.n),&lightDirectionU),0.0);
                    pixels[(x+y*WIDTH)*3] = (ambient+diff*lightPower)*255;
                    pixels[(x+y*WIDTH)*3+1] = (ambient+diff*lightPower)*255;
                    pixels[(x+y*WIDTH)*3+2] = (ambient+diff*lightPower)*255;
                }
            }
        }
    }
    double dot(Vertex *a, Vertex *b) {
        return a->x*b->x+a->y*b->y+a->z*b->z;
    }
    Vertex cross(Vertex *a, Vertex *b) {
        double newx = a->y*b->z-a->z*b->y;
        double newy = a->z*b->x-a->x*b->z;
        double newz = a->x*b->y-a->y*b->x;
        return Vertex{newx,newy,newz};
    }
};