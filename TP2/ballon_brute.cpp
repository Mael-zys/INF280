#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

double x_min, x_max, y_min, y_max, z_min, z_max;
int num_points;

vector<int> order;

void update_distance(int index, double r, vector<vector<double>> &dis){
    for(int i = index + 1; i < num_points; i++){
        dis[order[i]][order[index]] -= r;
        dis[order[index]][order[i]] -= r;            
    }
}

double find_r(double x[], double y[], double z[], vector<vector<double>> &dis, int index) {
    double r = dis[order[index]][order[index]];
    for (int i = 0; i < index; i++) {
        if (dis[order[index]][order[i]] < r) r = dis[order[index]][order[i]];
    }

    if (r > 0) update_distance(index,r,dis);
    else return 0.0;

    return r;
}

int main() {
    int count = 1;
    while (cin >> num_points) {
        if (num_points == 0) break;

        //read corner
        double temp[6];
        cin >> temp[0] >> temp[1] >> temp[2] >> temp[3] >> temp[4] >> temp[5];
        x_min = min(temp[0], temp[3]);
        x_max = max(temp[0], temp[3]);
        y_min = min(temp[1], temp[4]);
        y_max = max(temp[1], temp[4]);
        z_min = min(temp[2], temp[5]);
        z_max = max(temp[2], temp[5]);
        
        //read points
        double x[num_points];
        double y[num_points];
        double z[num_points];        
        vector<double>initialize(num_points, 0.0);
        vector<vector<double>> dis_points(num_points, initialize);
        for (int i = 0; i < num_points; i++) {
            cin >> x[i] >> y[i] >> z[i];
            for (int j = 0; j < i; j++) {
                dis_points[i][j] = dis_points[j][i] = sqrt((x[i]-x[j])*(x[i]-x[j]) + (y[i]-y[j])*(y[i]-y[j]) + (z[i]-z[j])*(z[i]-z[j]));
            }
            double temp1, temp2, temp3;
            temp1 = min(x[i]-x_min, x_max-x[i]);
            temp2 = min(y[i]-y_min, y_max-y[i]);
            temp3 = min(z[i]-z_min, z_max-z[i]);
            dis_points[i][i] = min(temp1, temp2);
            dis_points[i][i] = min(dis_points[i][i], temp3);
            order.push_back(i);
        }

        double volumn = 0;
        do {
            vector<vector<double>> dis_points_copy(dis_points.begin(), dis_points.end());
            double volumn_temp = 0;
            for(int index = 0; index < num_points; index++) {            
                double r = find_r(x,y,z,dis_points_copy, index);

                volumn_temp += 4/3.0*M_PI*pow(r,3);
            }
            volumn = max(volumn, volumn_temp);

        } while(next_permutation(order.begin(),order.end()));
        
        double box_volumn = fabs((x_max-x_min)*(y_max-y_min)*(z_max-z_min));

        order.clear();
        cout<<"Box "<< count<<": "<<(int)round(box_volumn - volumn)<<endl;
        cout<<endl;
        count++;
    }
    return 0;
}