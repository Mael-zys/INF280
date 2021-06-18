#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <limits.h>
#include <memory>
#include <vector>
using namespace std;

int x_min, x_max, y_min, y_max, z_min, z_max;
int num_points;
int num_rest;

void cal_distance(int x[], int y[], int z[], vector<vector<double>> &dis, double dis_to_box[]) {
    for (int i = 0; i < num_points; i++) {
        for (int j = i + 1; j < num_points; j++) {
            dis[i][j] = dis[j][i] = sqrt((x[i]-x[j])*(x[i]-x[j]) + (y[i]-y[j])*(y[i]-y[j]) + (z[i]-z[j])*(z[i]-z[j]));
        }
        double temp1, temp2, temp3;
        temp1 = min(x[i], x_max-x[i]);
        temp2 = min(y[i], y_max-y[i]);
        temp3 = min(z[i], z_max-z[i]);
        dis_to_box[i] = min(temp1, temp2);
        dis_to_box[i] = min(dis_to_box[i], temp3);
    }
}

double find_r(int x[], int y[], int z[], vector<vector<double>> &dis, double dis_to_box[], int flag = 1, int remove = -1) {
    double r = 9999999999/1.0;
    int index1 = -1;
    int index2 = -1;
    for (int i = 0; i < num_points; i++) {
        if (i == remove) continue;
        for (int j = i + 1; j < num_points; j++) {
            if (j==remove) continue;
            if (dis[i][j]/2.0 < r) {
                r = dis[i][j]/2.0;
                index1 = i;
                index2 = j;
            }
            // r = min(r, dis[i][j]/2.0);
        }
        if (dis_to_box[i]/1.0 < r) {
            r = dis_to_box[i]/1.0;
            index1 = i;
            index2 = -1;
        }
    }

    if (flag == 1) {
        // cout<< "index1 "<<index1<<" index2 "<<index2<<endl;
        vector<double>temp(num_points, 9999999999/1.0);
        if (index2 == -1) {
            // cout<<"index "<<index1<<endl;
            dis[index1]=temp;
            dis_to_box[index1] = 9999999999/1.0;
            for (int i = 0; i < num_points; i++)
                dis[i][index1] = 9999999999/1.0;
        }
        else {
            double r1 = find_r(x, y, z, dis, dis_to_box, 0, index1);
            double r2 = find_r(x, y, z, dis, dis_to_box, 0, index2);
            // cout<<"r1 "<<r1<<" r2 "<<r2<<endl;
            if (r1 >= r2) {
                // cout<<"index "<<index1<<endl;
                dis[index1]=temp; 
                dis_to_box[index1] = 9999999999/1.0;
                for (int i = 0; i < num_points; i++)
                    dis[i][index1] = 9999999999/1.0;
            }
            else {
                // cout<<"index "<<index2<<endl;
                dis[index2] = temp;
                dis_to_box[index2] = 9999999999/1.0;
                for (int i = 0; i < num_points; i++)
                    dis[i][index2] = 9999999999/1.0;
            }
        }
    }
    return r;
}

int main() {
    int count = 1;
    while (1) {
        cin >> num_points;
        if (num_points == 0) break;
        int temp[6];
        cin >> temp[0] >> temp[1] >> temp[2] >> temp[3] >> temp[4] >> temp[5];
        x_min = min(temp[0], temp[3]);
        x_max = max(temp[0], temp[3]);
        y_min = min(temp[1], temp[4]);
        y_max = max(temp[1], temp[4]);
        z_min = min(temp[2], temp[5]);
        z_max = max(temp[2], temp[5]);
        
        int x[num_points];
        int y[num_points];
        int z[num_points];
        for (int i = 0; i < num_points; i++) {
            cin >> x[i] >> y[i] >> z[i];
        }

        num_rest = num_points;
        // double dis_points[num_points][num_points];
        vector<double>temp1(num_points, 0.0);
        vector<vector<double>> dis_points(num_points, temp1);
        double dis_to_box[num_points];
        cal_distance(x,y,z, dis_points, dis_to_box);
        double volumn = 0;
        while(num_rest) {
            double r = find_r(x,y,z,dis_points,dis_to_box);
            // cout << "r :"<<r<<endl;
            // cout <<"num "<<num_rest<<endl;
            double volumn1 = num_rest*4/3.0*M_PI*pow(r,3);
            // cout <<"volumn1 "<<volumn1<<endl;
            volumn = max(volumn, volumn1);
            // cout <<"volumn "<<volumn<<endl;
            num_rest--;
        }
        double box_volumn = fabs((x_max-x_min)*(y_max-y_min)*(z_max-z_min));
        // cout<<"box volumn "<<box_volumn<<endl;
        
        cout<<"Box "<< count<<": "<<(int)round(box_volumn - volumn)<<endl;
        count++;
    }
    return 0;
}