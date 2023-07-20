#include <string>
#include <fstream>
#include <iostream>

class COLLADA {
private:
    struct TreeNode {
        std::string name;
        std::string content;
        std::string arguments;
        TreeNode *left = NULL;
        TreeNode *right = NULL;
        TreeNode *parent = NULL;
    };
    bool closed_tags = false;
    TreeNode *ROOT = new TreeNode;
public:
    COLLADA(std::string source) {
        // generate tree
        // find camera
        // find light
        // find materials
        // find vertices
        // find normals
        // find faces
        char charbuffer;
        std::string stringbuffer;
        std::fstream file(source,std::fstream::in);
        while (file >> std::noskipws >> charbuffer) {
            if (charbuffer=='\n') continue;
            if (charbuffer=='>'&&stringbuffer[0]!='?') {
                if (stringbuffer[0]=='/') { // closing tag
                    if (closed_tags) ROOT=ROOT->parent;
                    closed_tags = true;
                } else if (stringbuffer[stringbuffer.length()-1]=='/') { // "single tagger"
                    TreeNode *TEMP = new TreeNode{stringbuffer.substr(0,stringbuffer.find(" ",0))};
                    if (closed_tags) {
                        TEMP->parent = ROOT->parent;
                        ROOT->left = TEMP;
                        ROOT = TEMP;
                    } else {
                        TEMP->parent = ROOT;
                        ROOT->right = TEMP;
                    }
                } else { // opening tag
                    TreeNode *TEMP = new TreeNode{stringbuffer.substr(0,stringbuffer.find(" ",0))};
                    if (closed_tags) {
                        TEMP->parent = ROOT->parent;
                        ROOT->left = TEMP;
                        ROOT = TEMP;
                    } else {
                        TEMP->parent = ROOT;
                        ROOT->right = TEMP;
                        ROOT = TEMP;
                    }
                    closed_tags = false;
                }
                stringbuffer.clear();
            } else if (charbuffer=='<') {
                ROOT->content += stringbuffer;
                stringbuffer.clear();
            } else stringbuffer.push_back(charbuffer);
        }
    }
    void display_nodes(TreeNode *ROOT = NULL, int depth = 0) {
        if (ROOT==NULL) ROOT = this->ROOT;
        for (int i = 0 ; i < depth ; i++) std::cout << " ";
        std::cout << ROOT->name << std::endl;
        if (ROOT->right!=NULL) display_nodes(ROOT->right,depth+1);
        if (ROOT->left!=NULL) display_nodes(ROOT->left,depth);
    }
};

int main() {
    COLLADA *dae = new COLLADA("untitled.dae");
    dae->display_nodes();

    return 0;
}