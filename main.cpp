// default camera sensor size in blender - 36mm width
// default camera focal length in blender - 50mm length
// default camera render width in blender - 1920 px
// default camera render height in blender - 1080 px
#define WIDTH 1200
#define HEIGHT 1200
#define CHANNELS 3
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <math.h>
#include "lib/struct/vertex.cpp"
#include "lib/struct/face.cpp"
#include "lib/parser/obj_file.cpp"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "lib/encoder/stb_image_write.h"
#include "lib/camera/ray_casting.cpp"
// #include "lib/ray_casting.h"

#include <chrono>
using namespace std::chrono;

int main() {
    unsigned char *pixels = new unsigned char[WIDTH*HEIGHT*CHANNELS];
    auto start = high_resolution_clock::now();
    ObjFile *of = new ObjFile("model/untitled.obj");
    auto stop1 = high_resolution_clock::now();
    auto duration1 = duration_cast<microseconds>(stop1 - start);
    std::cout << "obj reader: " << duration1.count() << " microseconds" << std::endl;
    RayCasting *rc = new RayCasting(of,pixels);
    auto stop2 = high_resolution_clock::now();
    auto duration2 = duration_cast<microseconds>(stop2 - stop1);
    std::cout << "ray caster: " << duration2.count() << " microseconds" << std::endl;
    stbi_write_png("stbpng1.png", WIDTH, HEIGHT, CHANNELS, pixels, WIDTH * CHANNELS);
    return 0;
}