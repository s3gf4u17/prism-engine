// default camera sensor size in blender - 36mm width
// default camera focal length in blender - 50mm length
// default camera render width in blender - 1920 px
// default camera render height in blender - 1080 px

#include <iostream>
#include <fstream>
#include <math.h>
#include <string>
#include <vector>
#include <map>

#define WIDTH 120
#define HEIGHT 120

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "lib/stb_image_write.h"
#include "lib/prism_lin_alg.c"
#include "lib/prism_obj_file.cpp"
#include "lib/prism_ray_cast.cpp"

int main() {
    unsigned char *img = new unsigned char[WIDTH*HEIGHT*3];
    double *zbuf = new double[WIDTH*HEIGHT];
    for (int i = 0 ; i < WIDTH*HEIGHT ; i++) zbuf[i] = 1000000.0;
    Camera *camera = new Camera(Vertex{11.414,-6.89004,8.22334},Vertex{60.7593,0.000047,53.892});
    // Camera *camera = new Camera(Vertex{7.35889,-6.92579,4.95831},Vertex{63.5593,0,46.6919});
    Scene *scene = new Scene("model/untitled.obj",camera);
    RayCast *raycast = new RayCast(scene,img,zbuf);
    stbi_write_png("test.png", WIDTH,HEIGHT,3,img,WIDTH*3);
    return 0;
}