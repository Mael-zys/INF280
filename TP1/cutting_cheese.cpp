#include <iostream>
#include <string>
#include <math.h>  //use M_PI
#include <iomanip> //set output precision
#include <fstream>

using namespace std;

double X = 100.0, Y = 100.0, Z = 100.0;

double calculateSphere(double r) {
    return 4 / 3.0 * M_PI * r * r * r;
}

double calculateSphereSegment(double center, double r, double z) {
    double h = fabs(center - z);
    double r1Square = r * r - h * h;
    // formula of Segment sphérique 
    double volumn = 1 / 2.0 * calculateSphere(r);
    if (center < z) {
        volumn += 1 / 2.0 * M_PI * h * (r * r + r1Square + 1 / 3.0 * h * h);
    }
    else {
        volumn -= 1 / 2.0 * M_PI * h * (r * r + r1Square + 1 / 3.0 * h * h);
    }
    return volumn;
}

// calculate the volumn of holes in [0, z]
double calculateVolumn(double z, double hole[], int length) {
    double volumn = X * Y * z;
    for (int i = 0; 4 * i < length; i++) {
        if (z > hole[i * 4 + 1]) {  //hole[i*4 + 1] is z_left of the hole
            if (z >= hole[i * 4 + 2]) //hole[i*4 + 2] is z_right of the hole
                volumn -= calculateSphere(hole[i * 4]);
            else 
                volumn -= calculateSphereSegment(hole[i * 4 + 3], hole[i * 4], z);
        }
    }
    return volumn;
}

int main()
{
    int numHole, numSlice;
    while(cin >> numHole >> numSlice) {
    // fstream fin("input.txt");
    // ofstream fout("output.txt");
    // while(fin >> numHole >> numSlice) {
        double hole[numHole * 4];
        double volumnTotal = X * Y * Z;
        for (int i = 0; i < numHole; i++) {
            // each hole use 4 indexs: r, x, y, z
            cin >> hole[i * 4] >> hole[i * 4 + 1] >> hole[i * 4 + 2] >> hole[i * 4 + 3];
            // fin >> hole[i * 4] >> hole[i * 4 + 1] >> hole[i * 4 + 2] >> hole[i * 4 + 3];
            // x and y are useless, I replace them by z_left and z_right
            hole[i * 4 + 1] = hole[i * 4 + 3] - hole[i * 4];
            hole[i * 4 + 2] = hole[i * 4 + 3] + hole[i * 4];
            //change the dimension to millimeters
            hole[i * 4] /= 1000.0;
            hole[i * 4 + 1] /= 1000.0;
            hole[i * 4 + 2] /= 1000.0;
            hole[i * 4 + 3] /= 1000.0;
            // calculate the volumn of cheese
            volumnTotal -= calculateSphere(hole[i * 4]);
        }
        double volumnSlice = volumnTotal / numSlice;
        double slice[numSlice];
        slice[0] = 0;
        // only need to cut numSlice-1 times
        for (int i = 1; i < numSlice; i++) {
            double volumnObjective = volumnSlice * i;
            //dichotomy
            double left = slice[i - 1], right = Z;
            double mid = (left + right) / 2.0;
            double tempVolumn = calculateVolumn(mid, hole, numHole * 4);
            while (fabs(tempVolumn - volumnObjective) > 1e-6  && fabs(right - left) > 1e-6) {
                if (tempVolumn > volumnObjective)
                    right = mid;
                else left = mid;
                mid = (left + right) / 2.0;
                tempVolumn = calculateVolumn(mid, hole, numHole * 4);
            }
            slice[i] = mid;
            cout << fixed << setprecision(9) << slice[i] - slice[i - 1] << endl;
            // fout << fixed << setprecision(9) << slice[i] - slice[i - 1] << endl;
        }
        cout << fixed << setprecision(9) << Z - slice[numSlice - 1] << endl;
        // fout << fixed << setprecision(9) << Z - slice[numSlice - 1] << endl;
    }
    // fin.close();
    // fout.close();
    // g++ -o cutting cutting_cheese.cpp
    // diff result.txt output.txt -y
    return 0;
}