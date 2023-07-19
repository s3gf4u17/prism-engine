#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <math.h>

#include "lib/struct/vertex.cpp"
#include "lib/struct/face.cpp"
#include "lib/parser/obj_file.cpp"

int main() {
    ObjFile *of = new ObjFile("untitled.obj");
    std::cout << of << std::endl;
    return 0;
}