#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <limits.h>
#include <memory>
#include <vector>
#include <unordered_set>
using namespace std;

double x_min, x_max, y_min, y_max, z_min, z_max;
int num_points;
// int num_rest;
unordered_set<int> choice;

void cal_distance(double x[], double y[], double z[], vector<vector<double>> &dis) {
    for (int i = 0; i < num_points; i++) {
        for (int j = i + 1; j < num_points; j++) {
            dis[i][j] = dis[j][i] = sqrt((x[i]-x[j])*(x[i]-x[j]) + (y[i]-y[j])*(y[i]-y[j]) + (z[i]-z[j])*(z[i]-z[j]));
        }
        double temp1, temp2, temp3;
        temp1 = min(x[i]-x_min, x_max-x[i]);
        temp2 = min(y[i]-y_min, y_max-y[i]);
        temp3 = min(z[i]-z_min, z_max-z[i]);
        dis[i][i] = min(temp1, temp2);
        dis[i][i] = min(dis[i][i], temp3);
    }
}

void update_distance(int index, double r, vector<vector<double>> &dis){
    for(int i = 0; i < num_points; i++){
        if (!choice.count(i)){
            dis[i][index] -= r;
            dis[index][i] -= r;
            
            if (dis[i][index] <= 0.0) {
                choice.insert(i);
                // cout<<"size "<<choice.size()<<endl;
                for(int j = 0; j < num_points; j++) 
                    dis[j][i] = dis[i][j] = 999999999.0/1.0;
            } 
        }

    }
}

double find_r(double x[], double y[], double z[], vector<vector<double>> &dis) {
    double r = -1.0;
    int index = 0;
    for (int i = 0; i < num_points; i++) {
        if (choice.empty()){
            if (dis[i][i] > r) {
                r = dis[i][i];
                index = i;
            }
        }
        else {
            if (choice.count(i)) continue;
            double temp = dis[i][i];
            for (int j = 0; j < num_points; j++) {
                if (!choice.count(j)) continue;
                temp = min(temp, dis[i][j]);
            }
            if (temp > r) {
                r = temp;
                index = i;
            }
        }
    }
    // cout<<"index "<<index<<endl;
    choice.insert(index);
    update_distance(index,r,dis);
    
    return r;
}

int main() {
    int count = 1;
    while (cin >> num_points) {
        if (num_points == 0) break;
        double temp[6];
        cin >> temp[0] >> temp[1] >> temp[2] >> temp[3] >> temp[4] >> temp[5];
        x_min = min(temp[0], temp[3]);
        x_max = max(temp[0], temp[3]);
        y_min = min(temp[1], temp[4]);
        y_max = max(temp[1], temp[4]);
        z_min = min(temp[2], temp[5]);
        z_max = max(temp[2], temp[5]);
        
        double x[num_points];
        double y[num_points];
        double z[num_points];
        for (int i = 0; i < num_points; i++) {
            cin >> x[i] >> y[i] >> z[i];
        }

        choice.clear();
        // num_rest = num_points;
        // double dis_points[num_points][num_points];
        vector<double>temp1(num_points, 0.0);
        vector<vector<double>> dis_points(num_points, temp1);
        cal_distance(x,y,z, dis_points);
        double volumn = 0;
        while(choice.size() < num_points) {
            double r = find_r(x,y,z,dis_points);
            // cout << "r :"<<r<<endl;
            // cout <<"num "<<num_rest<<endl;
            volumn += 4/3.0*M_PI*pow(r,3);
            // cout <<"volumn "<<volumn<<endl;
            // num_rest--;
        }
        double box_volumn = fabs((x_max-x_min)*(y_max-y_min)*(z_max-z_min));
        // cout<<"box volumn "<<box_volumn<<endl;
        
        cout<<"Box "<< count<<": "<<(int)round(box_volumn - volumn)<<endl;
        cout<<endl;
        count++;
    }
    return 0;
}