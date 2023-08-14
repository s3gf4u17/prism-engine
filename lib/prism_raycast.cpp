#include <prism_raycast.h>
#include <iostream>

RayCast::RayCast(Scene *scene, unsigned char *img, double *zbuf, Camera* camera) {
        double lx0 = lpos.x-camera->pos.x;
        double ly0 = lpos.y-camera->pos.y;
        double lz0 = lpos.z-camera->pos.z;
        double lx1 = cos(-camera->rot.z/180.0*M_PI)*lx0-sin(-camera->rot.z/180.0*M_PI)*ly0;
        double ly1 = sin(-camera->rot.z/180.0*M_PI)*lx0+cos(-camera->rot.z/180.0*M_PI)*ly0;
        double lx2 = cos(-camera->rot.y/180.0*M_PI)*lx1-sin(-camera->rot.y/180.0*M_PI)*lz0;
        double lz2 = sin(-camera->rot.y/180.0*M_PI)*lx1+cos(-camera->rot.y/180.0*M_PI)*lz0;
        double ly3 = cos(-camera->rot.x/180.0*M_PI)*ly1-sin(-camera->rot.x/180.0*M_PI)*lz2;
        double lz3 = sin(-camera->rot.x/180.0*M_PI)*ly1+cos(-camera->rot.x/180.0*M_PI)*lz2;
        lpos.x = lx2;
        lpos.y = ly3;
        lpos.z = lz3;
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
                        // find intersection point for lighting calculations
                        Vertex intersection;
                        intersection.x = face.a.x*(1-u-v)+face.b.x*u+face.c.x*v;
                        intersection.y = face.a.y*(1-u-v)+face.b.y*u+face.c.y*v;
                        intersection.z = face.a.z*(1-u-v)+face.b.z*u+face.c.z*v;
                        Vertex inttolight;
                        inttolight.x = lpos.x-intersection.x;
                        inttolight.y = lpos.y-intersection.y;
                        inttolight.z = lpos.z-intersection.z;
                        float distance = sqrt(dot(&inttolight,&inttolight));
                        Vertex lightdirection(inttolight.x/distance,inttolight.y/distance,inttolight.z/distance);
                        float lpowl = lpow/distance;
                        // avg normal - using x and y
                        Vertex normal;
                        normal.x = face.n.x*(1-u-v)+face.nb.x*u+face.nc.x*v;
                        normal.y = face.n.y*(1-u-v)+face.nb.y*u+face.nc.y*v;
                        normal.z = face.n.z*(1-u-v)+face.nb.z*u+face.nc.z*v;
                        double normalL = sqrt(dot(&normal,&normal));
                        Vertex normalU(normal.x/normalL,normal.y/normalL,normal.z/normalL);
                        double diff = std::max(dot(&normalU,&lightdirection),0.0);
                        // double diff = std::max(dot(&face.n,&lightU),0.0);
                        if ((x+y*WIDTH)*3>0&&(x+y*WIDTH)*3<WIDTH*HEIGHT*3) img[(x+y*WIDTH)*3] = std::min((int)((ambientW+diff*lpowl)*face.R),255);
                        if ((x+y*WIDTH)*3+1>0&&(x+y*WIDTH)*3+1<WIDTH*HEIGHT*3) img[(x+y*WIDTH)*3+1] = std::min((int)((ambientW+diff*lpowl)*face.G),255);
                        if ((x+y*WIDTH)*3+2>0&&(x+y*WIDTH)*3+2<WIDTH*HEIGHT*3) img[(x+y*WIDTH)*3+2] = std::min((int)((ambientW+diff*lpowl)*face.B),255);
                    }
                }
            }
        }
    }