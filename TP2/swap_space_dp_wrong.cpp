#include <iostream>
#include <stdlib.h>

using namespace std;

int main() {
    long long int num_drive;
    while (cin >> num_drive) {

        //read drive
        long long int new_drive[num_drive];
        long long int old_drive[num_drive]; 
        long long int diff[num_drive];       
        for(long long int i = 0; i < num_drive; i++) {
            cin >> old_drive[i] >> new_drive[i];
            if(i == 0) diff[0] = new_drive[0] - old_drive[0];
            else diff[i] = diff[i - 1] + new_drive[i] - old_drive[i];
        }
        
        // dp
        long long int dp[num_drive];
        dp[0] = old_drive[0];
        for (long long int i = 1; i < num_drive; i++) {
            //case 1
            long long int rest = diff[i - 1] + dp[i - 1] - old_drive[i];
            if(rest >= 0) dp[i] = dp[i - 1];
            else dp[i] = dp[i - 1] - rest;

            //case 2
            rest = new_drive[i] - dp[i - 1];
            if(rest >= 0) dp[i] = min(dp[i], old_drive[i]);
            else dp[i] = min(dp[i], old_drive[i] - rest);
        }        

        cout << dp[num_drive - 1] << endl;
    }
    return 0;
}