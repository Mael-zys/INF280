#include <iostream>
#include <stdlib.h>
#include <vector>
#include <algorithm>
using namespace std;

bool compare1(vector<long long int> drive1, vector<long long int> drive2){
    if (drive1[0] == drive2[0]) return drive1[1] > drive2[1];
    return drive1[0] < drive2[0];
}

bool compare2(vector<long long int> drive1, vector<long long int> drive2){
    if (drive1[1] == drive2[1]) return drive1[0] < drive2[0];
    return drive1[1] > drive2[1];
}

int main() {
    long long int num_drive;
    while (cin >> num_drive) {

        //read drive
        vector<vector<long long int>> drive_get; 
        vector<vector<long long int>> drive_loss;    
        long long int drive_old, drive_new;
        for(long long int i = 0; i < num_drive; i++) {
            cin >> drive_old >> drive_new;
            if (drive_old < drive_new){
                drive_get.push_back(vector<long long int> {drive_old, drive_new});
            }
            else {
                drive_loss.push_back(vector<long long int> {drive_old, drive_new});
            }
        }

        //sort
        sort(drive_get.begin(), drive_get.end(), compare1); 
        sort(drive_loss.begin(), drive_loss.end(), compare2);

        //merge
        drive_get.insert(drive_get.end(), drive_loss.begin(), drive_loss.end());
        
        //greedy
        long long int cost = 0, diff = 0;
        for (auto & drive : drive_get){
            if (cost + diff < drive[0]) {
                cost = (drive[0] - diff);
                
            }
            diff += (drive[1] - drive[0]); 
        }

        cout << cost << endl;
    }
    return 0;
}