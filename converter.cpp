#include <fstream>
#include <string>
#include <iostream>
#include <math.h>

const double cp[3] = {11.414,-6.89003,8.22335};
const double cr[3] = {60.7593,0.000049,53.892};

int main() {
    std::ifstream in("in.obj");
    std::ofstream out("out.obj");

    std::string line;

    while (getline(in,line)) {
        if (line[0]=='v'&&line[1]!='n'&&line[1]!='t') {
            int e1 = line.find(" ",2);
            int e2 = line.find(" ",e1+1);
            double x = std::stod(line.substr(2,e1-2));
            double y = std::stod(line.substr(e1+1,e2-e1-1));
            double z = std::stod(line.substr(e2+1,line.length()-e2));
            x -= cp[0];
            y -= cp[1];
            z -= cp[2];
            // rotate around z
            double x1 = cos(-cr[2]/180.0*M_PI)*x-sin(-cr[2]/180.0*M_PI)*y;
            double y1 = sin(-cr[2]/180.0*M_PI)*x+cos(-cr[2]/180.0*M_PI)*y;
            double z1 = z;
            // rotate around y
            double x2 = cos(-cr[1]/180.0*M_PI)*x1+sin(-cr[1]/180.0*M_PI)*z1;
            double y2 = y1;
            double z2 = -sin(-cr[1]/180.0*M_PI)*x1+cos(-cr[1]/180.0*M_PI)*z1;
            // rotate around x
            double x3 = x2;
            double y3 = cos(-cr[0]/180.0*M_PI)*y2-sin(-cr[0]/180.0*M_PI)*z2;
            double z3 = sin(-cr[0]/180.0*M_PI)*y2+cos(-cr[0]/180.0*M_PI)*z2;

            out << "v " << x3 << " " << y3 << " " << z3 << std::endl;
        } else {
            out << line << std::endl;
        }
    }

    in.close();
    out.close();
    return 0;
}