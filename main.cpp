// default camera sensor size in blender - 36mm width
// default camera focal length in blender - 50mm length
// default camera render width in blender - 1920 px
// default camera render height in blender - 1080 px

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>
#include <prism_config.h>
#include <prism_models.h>
#include <prism_linalg.h>
#include <prism_raycast.h>

int main() {
    unsigned char *img = new unsigned char[WIDTH*HEIGHT*3];
    double *zbuf = new double[WIDTH*HEIGHT];
    for (int i = 0 ; i < WIDTH*HEIGHT ; i++) zbuf[i] = 1000000.0;
    Camera *camera = new Camera(Vertex{11.414,-6.89004,8.22334},Vertex{60.7593,0.000047,53.892});
    // Camera *camera = new Camera(Vertex{7.35889,-6.92579,4.95831},Vertex{63.5593,0,46.6919}); // <-- default blender camera
    Scene *scene = new Scene("test/untitled.obj",camera);
    RayCast *raycast = new RayCast(scene,img,zbuf,camera);
    stbi_write_png("test/untitled.png", WIDTH,HEIGHT,3,img,WIDTH*3);
    return 0;
}