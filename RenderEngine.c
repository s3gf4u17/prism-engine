#include <cstdint>
#include <stdio.h>
#define SCREEN_HEIGHT 400
#define SCREEN_WIDTH 400
#define FOCAL_LENGTH 90
#define CHANNELS 3

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

void draw(uint8_t *pixels,uint32_t *xs,uint32_t *ys) {
    printf("%i\t%i\n",xs[0],xs[1]);
    printf("%i\t%i\n",ys[0],ys[1]);
    for (int y = ys[0];y < ys[1]; y++) {
        for (int x = xs[0];x < xs[1]; x++) {
            pixels[(x+y*SCREEN_WIDTH)*3+1]=255;
        }
    }
}

void transform() {
}

void save() {
}

int main() {
    uint8_t* pixels = new uint8_t[SCREEN_HEIGHT*SCREEN_WIDTH*CHANNELS];
    uint32_t xs[] = {0,200};
    uint32_t ys[] = {0,200};
    draw(pixels,xs,ys);

    stbi_write_png("stbpng.png",SCREEN_WIDTH,SCREEN_HEIGHT,CHANNELS,pixels,SCREEN_WIDTH*CHANNELS);
    return 0;
}