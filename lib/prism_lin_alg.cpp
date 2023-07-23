#include <iostream>

class Vector3d {
public:
    double x;
    double y;
    double z;
    Vector3d(double x, double y, double z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }
    Vector3d operator -(Vector3d right) { // subtraction
        double newx = this->x-right.x;
        double newy = this->y-right.y;
        double newz = this->z-right.z;
        return Vector3d(newx,newy,newz);
    }
    Vector3d cross(Vector3d right) { // cross product
        double newx = this->y*right.z-this->z*right.y;
        double newy = this->z*right.x-this->x*right.z;
        double newz = this->x*right.y-this->y*right.x;
        return Vector3d(newx,newy,newz);
    }
    double dot(Vector3d right) { // dot product
        return this->x*right.x+this->y*right.y+this->z*right.z;
    }
};

int main() {
    Vector3d a(3,-5,4);
    Vector3d b(2,6,5);

    Vector3d c = a.cross(b);
    double dot = a.dot(b);

    std::cout << c.x << "\t" << c.y << "\t" << c.z << std::endl;
    std::cout << dot << std::endl;
    return 0;
}