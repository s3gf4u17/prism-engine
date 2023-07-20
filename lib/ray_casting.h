class RayCasting {
private:
    Vertex cameraP{11.414,-6.89003,8.22335};
    Vertex cameraR{60.7593,0.000049,53.892};
public:
    RayCasting(ObjFile *of, unsigned char *pixels) {
        for (Face face : of->faces) {
            Vertex A{face.a.x-cameraP.x,face.a.y-cameraP.y,face.a.z-cameraP.z};
            Vertex B{face.b.x-cameraP.x,face.b.y-cameraP.y,face.b.z-cameraP.z};
            Vertex C{face.c.x-cameraP.x,face.c.y-cameraP.y,face.c.z-cameraP.z};
            // define vector from camera to point
            // get vector cross point with sensor
            // paint triangle
        }
    }
};