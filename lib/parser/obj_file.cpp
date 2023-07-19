class ObjFile {
public:
    std::vector<Vertex> vertices;
    std::vector<Face> faces;
    ObjFile (std::string source) {
        std::fstream file(source);
        std::string linebuffer;
        if (file.is_open()) {
            while (getline(file,linebuffer)) {
                std::vector<std::string> elements;
                std::string tempbuffer;
                for (char c : linebuffer) {
                    if (c==' '||c=='/') {
                        elements.push_back(tempbuffer);
                        tempbuffer.clear();
                    } else tempbuffer.push_back(c);
                } if(!tempbuffer.empty()) elements.push_back(tempbuffer);
                if (elements[0]=="v") {
                    process_vertex(elements);
                } else if (elements[0]=="f") process_face(elements);
            }
        }
    }
    void process_vertex(std::vector<std::string> elements){
        Vertex vertex;
        vertex.x = stod(elements[1]);
        vertex.y = stod(elements[2]);
        vertex.z = stod(elements[3]);
        vertices.push_back(vertex);
    }
    void process_face(std::vector<std::string> elements){
        std::vector<int> pointers;
        for (int i = 1 ; i < elements.size() ; i++) {
            if((i-1)%3==0) pointers.push_back(stoi(elements[i])-1);
        }
        for (int i = 1 ; i < pointers.size()-1 ; i++) {
            Face face;
            face.a = vertices[pointers[0]];
            face.b = vertices[pointers[i]];
            face.c = vertices[pointers[i+1]];
            Vertex p2p1 = Vertex{face.b.x-face.a.x,face.b.y-face.a.y,face.b.z-face.a.z};
            Vertex p3p1 = Vertex{face.c.x-face.a.x,face.c.y-face.a.y,face.c.z-face.a.z};
            face.n.x = p2p1.y*p3p1.z-p2p1.z*p3p1.y;
            face.n.y = p2p1.z*p3p1.x-p2p1.x*p3p1.z;
            face.n.z = p2p1.x*p3p1.y-p2p1.y*p3p1.x;
            double nlength = sqrt(pow(face.n.x,2)+pow(face.n.y,2)+pow(face.n.z,2));
            face.n.x /= nlength;
            face.n.y /= nlength;
            face.n.z /= nlength;
            faces.push_back(face);
        }
    }
    friend std::ostream & operator <<(std::ostream &os, ObjFile *of) {
        for (Face face : of->faces) {
            os << "a [" << face.a.x << "\t" << face.a.y << "\t" << face.a.z << "]\t";
            os << "b [" << face.b.x << "\t" << face.b.y << "\t" << face.b.z << "]\t";
            os << "c [" << face.c.x << "\t" << face.c.y << "\t" << face.c.z << "]\t";
            os << "n [" << face.n.x << "\t" << face.n.y << "\t" << face.n.z << "]\n";
        }
        return os;
    }
};