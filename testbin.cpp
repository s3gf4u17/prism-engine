#include <iostream>
#include <fstream>
using namespace std;

struct Vertex {
    float x;
    float y;
    float z;
};

struct Normal {
    float x;
    float y;
    float z;
};

struct Face {
    int a;
    int b;
    int c;
};

struct Material {
    char r;
    char g;
    char b;
};

struct Config {
    float cpx,cpy,cpz;
    float crx,cry,crz;
    int vc,nc,fc,mc;
};

int main() {
    ifstream in("prism.bin",ios::out|ios::binary);
    Config config;
    in.read((char *)&config,sizeof(Config));
    cout << config.cpx << "\t" << config.vc << endl;
    in.close();
    return 0;
}