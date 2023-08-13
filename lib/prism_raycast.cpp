#include <prism_raycast.h>
#include <iostream>

RayCast::RayCast(Scene *scene, unsigned char *img, double *zbuf) {
        for (Object object : scene->objects) {
            for (Face face : object.faces) {
                float multa = 50.0/face.a.z;
                float multb = 50.0/face.b.z;
                float multc = 50.0/face.c.z;
                float xmax = std::max(std::max(face.a.x*multa,face.b.x*multb),face.c.x*multc);
                float xmin = std::min(std::min(face.a.x*multa,face.b.x*multb),face.c.x*multc);
                float ymax = std::max(std::max(face.a.y*multa,face.b.y*multb),face.c.y*multc);
                float ymin = std::min(std::min(face.a.y*multa,face.b.y*multb),face.c.y*multc);
                for (int y = ymin/sensh*HEIGHT+HEIGHT/2 ; y < ymax/sensh*HEIGHT+HEIGHT/2 ; y++) {
                    for (int x = -xmax/sensw*WIDTH+WIDTH/2 ; x < -xmin/sensw*WIDTH+WIDTH/2 ; x++) {
                        Vertex rayN(-sensw/2.0+(x+0.5)*(sensw/WIDTH),sensh/2.0-(y+0.5)*(sensh/HEIGHT),-50.0);
                        double rayL = sqrt(dot(&rayN,&rayN));
                        Vertex rayU(rayN.x/rayL,rayN.y/rayL,rayN.z/rayL);
                        const float EPSILON = 0.0000001;
                        Vertex edge1(face.b.x-face.a.x,face.b.y-face.a.y,face.b.z-face.a.z);
                        Vertex edge2(face.c.x-face.a.x,face.c.y-face.a.y,face.c.z-face.a.z);
                        Vertex h = cross(&rayU,&edge2);
                        double a = dot(&edge1,&h);
                        if (a > -EPSILON && a < EPSILON) continue; // parallel
                        double f = 1.0/a;
                        Vertex s(-face.a.x,-face.a.y,-face.a.z);
                        double u = f * dot(&s,&h);
                        if (u < 0.0 || u > 1.0) continue;
                        Vertex q = cross(&s,&edge1);
                        double v = f * dot(&rayU,&q);
                        if (v < 0.0 || u + v > 1.0) continue;
                        double t = f * dot(&edge2,&q);
                        if (x+y*WIDTH<0||x+y*WIDTH>WIDTH*HEIGHT) continue;
                        if (t<EPSILON||t>zbuf[x+y*WIDTH]) continue;
                        zbuf[x+y*WIDTH]=t;
                        // avg normal - using x and y
                        Vertex normal;
                        normal.x = face.n.x*(1-u-v)+face.nb.x*u+face.nc.x*v;
                        normal.y = face.n.y*(1-u-v)+face.nb.y*u+face.nc.y*v;
                        normal.z = face.n.z*(1-u-v)+face.nb.z*u+face.nc.z*v;
                        double normalL = sqrt(dot(&normal,&normal));
                        Vertex normalU(normal.x/normalL,normal.y/normalL,normal.z/normalL);
                        double diff = std::max(dot(&normalU,&lightU),0.0);
                        // double diff = std::max(dot(&face.n,&lightU),0.0);
                        if ((x+y*WIDTH)*3>0&&(x+y*WIDTH)*3<WIDTH*HEIGHT*3) img[(x+y*WIDTH)*3] = std::min((int)((ambientW+diff*lightW)*face.R),255);
                        if ((x+y*WIDTH)*3+1>0&&(x+y*WIDTH)*3+1<WIDTH*HEIGHT*3) img[(x+y*WIDTH)*3+1] = std::min((int)((ambientW+diff*lightW)*face.G),255);
                        if ((x+y*WIDTH)*3+2>0&&(x+y*WIDTH)*3+2<WIDTH*HEIGHT*3) img[(x+y*WIDTH)*3+2] = std::min((int)((ambientW+diff*lightW)*face.B),255);
                    }
                }
            }
        }
    }