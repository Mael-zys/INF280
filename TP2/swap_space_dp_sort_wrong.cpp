#include <iostream>
#include <stdlib.h>
#include <vector>
#include <algorithm>
using namespace std;

bool compare1(vector<long long int> drive1, vector<long long int> drive2){
    return drive1[1] > drive2[1];
}

bool compare2(vector<long long int> drive1, vector<long long int> drive2){
    return drive1[1] < drive2[1];
}

int main() {
    long long int num_drive;
    while (cin >> num_drive) {

        //read drive
        vector<vector<long long int>> drive(num_drive, vector<long long int>(3, 0));     
        for(long long int i = 0; i < num_drive; i++) {
            cin >> drive[i][1] >> drive[i][2];
            drive[i][0] = drive[i][2] - drive[i][1];
        }

        //sort by new - old
        sort(drive.begin(), drive.end(), greater<vector<long long int>>());
        // for new - old < 0, sort by old
        int temp = 0;
        for (; temp < num_drive; temp++) 
            if (drive[temp][0] < 0) break;
        sort(drive.begin() + temp, drive.end(), compare1); 
        sort(drive.begin(), drive.begin() + temp, compare2);
        // for (int i = 0; i < num_drive; i++) {
        //     if (drive[i][0] < 0) {
        //         for (int j = i + 1; j < num_drive; j++) {
        //             if (drive[i][1] < drive[j][1]) 
        //                 drive[i].swap(drive[j]);
        //         }
        //     }
        // }


        // for (auto & i:drive)
        //     cout<<i[0]<<" "<<endl;
        
        // dp
        long long int dp[num_drive];
        long long int diff;
        dp[0] = drive[0][1];
        diff = drive[0][2] - drive[0][1];
        for (long long int i = 1; i < num_drive; i++) {
            //case 1
            long long int rest = diff + dp[i - 1] - drive[i][1];
            if(rest >= 0) dp[i] = dp[i - 1];
            else dp[i] = dp[i - 1] - rest;
            // cout<<"rest1 "<<rest<<endl;

            //case 2
            rest = drive[i][2] - dp[i - 1];
            if(rest >= 0) dp[i] = min(dp[i], drive[i][1]);
            else dp[i] = min(dp[i], drive[i][1] - rest);

            diff += drive[i][2] - drive[i][1];
            // cout<<"rest2 "<<rest<<endl;
            // cout<<"dp "<<dp[i]<<endl;
        }        

        cout << dp[num_drive - 1] << endl;
    }
    return 0;
}