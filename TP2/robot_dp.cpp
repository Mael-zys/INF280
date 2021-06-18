#include <iostream>
#include <stdlib.h>
#include <limits.h>
#include <vector>

using namespace std;

vector<int> dp;

//calculate the distance in this tour
int cal_dis(vector<vector<int>> &v, int left, int right) {
    int dis = abs(v[left][0]) + abs(v[left][1]) + abs(v[right][0]) + abs(v[right][1]);
    for (int i = left + 1; i <= right; i++) 
        dis += abs(v[i][0] - v[i - 1][0]) + abs(v[i][1] - v[i - 1][1]);
    return dis;
}

int main() {
    int num_case = 0;
    cin >> num_case;

    for(int i = 0; i < num_case; i++) {
        int num_mail;
        int capacity;
        cin >> capacity >> num_mail;
        vector<vector<int>> mails;

        //read input of mails
        for(int j = 0; j < num_mail; j++) {
            vector<int> mail(3, 0);
            cin >> mail[0] >> mail[1] >> mail[2]; 
            mails.push_back(mail);
        }
        dp.clear();
        int right = 0;
        
        // initialisation
        dp.push_back(2 * abs(mails[0][0]) + 2 * abs(mails[0][1]));
        
        // dp
        for (int j = 1; j < num_mail; j++) {
            int num_cap = 0;
            int dis = INT_MAX;
            for (int k = j; k >=0; k--) {
                num_cap += mails[k][2];
                if (num_cap > capacity) break;
                if (k >= 1) dis = min(dis, cal_dis(mails, k, j) + dp[k - 1]);
                else dis = min(dis, cal_dis(mails, k ,j));
            }
            dp.push_back(dis);
        }

        //print the result
        if (i != 0) cout << endl;
        cout << dp[num_mail - 1] << endl;
    }

    return 0;
}