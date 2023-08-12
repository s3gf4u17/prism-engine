struct LibraryCamera {
    std::string id;
    double xfov;
    double aspect_ratio;
    double znear;
    double zfar;
    double shiftx;
    double shifty;
    double dof_distance;
};

struct Camera {
    double matrix[4][4];
    LibraryCamera* libcam;
};

struct Node {
    std::string tag;
    std::string ins;
    Node *left;
    Node *right;
    Node *parent;
};

class COLLADA {
private:
    Node *ROOT = new Node;
    bool marker = false;
public:
    std::vector<LibraryCamera> libcams;
    COLLADA() {
        read();
        extract_cameras(ROOT);
    }
    void read() {
        char c; std::string s; std::fstream f("model/untitled.dae",std::fstream::in);
        while (f >> std::noskipws >> c) {
            if (c=='\n') continue;
            if (c=='>'&&s[0]!='?') {
                if (s[0]=='/') {
                    if (marker) ROOT = ROOT->parent;
                    marker = true;
                } else if (s[s.length()-1]=='/') {
                    Node *LEAF = new Node{s.substr(0,s.find(" ",0))};
                    if (marker) {
                        LEAF->parent = ROOT->parent;
                        ROOT-> left = LEAF;
                        ROOT = LEAF;
                    } else {
                        LEAF->parent = ROOT;
                        ROOT->right = LEAF;
                    }
                } else {
                    Node *LEAF = new Node{s.substr(0,s.find(" ",0))};
                    if (marker) {
                        LEAF->parent = ROOT->parent;
                        ROOT->left = LEAF;
                        ROOT = LEAF;
                    } else {
                        LEAF->parent = ROOT;
                        ROOT->right = LEAF;
                        ROOT = LEAF;
                    }
                    marker = false;
                } s.clear();
            } else if (c=='<') {
                ROOT->ins += s;
                s.clear();
            } else s.push_back(c);
        }
    }
    void extract_cameras(Node *ROOT) {
        switch (std::str2int(ROOT->tag)) {
            case std::str2int("author"): std::cout << ROOT->ins << std::endl;
        };
        if (ROOT->right!=NULL) extract_cameras(ROOT->right);
        if (ROOT->left!=NULL) extract_cameras(ROOT->left);
    }
};

// class COLLADA {
// private:
//     struct TreeNode {
//         std::string name;
//         std::string content;
//         std::string properties;
//         TreeNode *left = NULL;
//         TreeNode *right = NULL;
//         TreeNode *parent = NULL;
//     };
//     TreeNode *ROOT = new TreeNode;
//     bool marker = false;
// public:
//     COLLADA(std::string source) {
//         generate_tree(source);
//         // generate tree
//         // find camera
//         // find light
//         // find materials
//         // find vertices
//         // find normals
//         // find faces
//     }
//     void generate_tree(std::string source) {
//         char charbuffer;
//         std::string stringbuffer;
//         std::fstream file(source,std::fstream::in);
//         while (file >> std::noskipws >> charbuffer) {
//             if (charbuffer=='\n') continue;
//             if (charbuffer=='>'&&stringbuffer[0]!='?') {
//                 if (stringbuffer[0]=='/') {
//                     if (marker) ROOT = ROOT->parent;
//                     marker = true;
//                 } else if (stringbuffer[stringbuffer.length()-1]=='/') {
//                     TreeNode *TEMP = new TreeNode;
//                     size_t found = stringbuffer.find(" ",0);
//                     TEMP->name = stringbuffer.substr(0,found);
//                     if (found!=std::string::npos) TEMP->properties = stringbuffer.substr(found+1,stringbuffer.length()-found);
//                     if (marker) {
//                         TEMP->parent = ROOT->parent;
//                         ROOT->left = TEMP;
//                         ROOT = TEMP;
//                     } else {
//                         TEMP->parent = ROOT;
//                         ROOT->right = TEMP;
//                     }
//                 } else {
//                     TreeNode *TEMP = new TreeNode;
//                     size_t found = stringbuffer.find(" ",0);
//                     TEMP->name = stringbuffer.substr(0,stringbuffer.find(" ",0));
//                     if (found!=std::string::npos) TEMP->properties = stringbuffer.substr(found+1,stringbuffer.length()-found);
//                     if (marker) {
//                         TEMP->parent = ROOT->parent;
//                         ROOT->left = TEMP;
//                         ROOT = TEMP;
//                     } else {
//                         TEMP->parent = ROOT;
//                         ROOT->right = TEMP;
//                         ROOT = TEMP;
//                     }
//                     marker = false;
//                 }
//                 stringbuffer.clear();
//             } else if (charbuffer=='<') {
//                 ROOT->content += stringbuffer;
//                 stringbuffer.clear();
//             } else stringbuffer.push_back(charbuffer);
//         }
//     }
//     friend std::ostream& operator <<(std::ostream& os, COLLADA *dae) {
//         os << "test";
//         return os;
//     }
// };