#include <iostream>
#include <stdlib.h>
#include <vector>
#include <unordered_map>
#include <limits.h>

using namespace std;

int capacity;

unordered_map<int, int> M;

int cal_dis(vector<vector<int>> &v, int left, int right) {
    int dis = abs(v[left][0]) + abs(v[left][1]) + abs(v[right][0]) + abs(v[right][1]);
    for (int i = left + 1; i <= right; i++) 
        dis += abs(v[i][0] - v[i - 1][0]) + abs(v[i][1] - v[i - 1][1]);
    return dis;
}

int fin_min_dis(vector<vector<int>> &v, int cap, int left) {
    int sum_cap = 0;
    int dis = INT_MAX;
    if (left >= v.size()) return 0;
    if (M[left]) return M[left];
    for (int i = left; i < v.size(); i++) {
        sum_cap += v[i][2];
        if (sum_cap > cap) break;
        dis = min(dis, cal_dis(v, left, i) + fin_min_dis(v, cap, i + 1));
    }
    M[left] = dis;
    return dis;
}

int main() {
    int num_case = 0;
    cin >> num_case;
    // cout << "cases: " << num_case <<endl;
    for(int i = 0; i < num_case; i++) {
        int num_mail;
        cin >> capacity >> num_mail;
        vector<vector<int>> mails;
        // cout<< capacity << "   " <<num_mail<<endl;
        for(int j = 0; j < num_mail; j++) {
            vector<int> mail(3, 0);
            cin >> mail[0] >> mail[1] >> mail[2];
            // cout<< mail[0] << "   " << mail[1] << "   " << mail[2] << endl; 
            mails.push_back(mail);
        }
        M.clear();
        int left = 0;
        int min_distance = fin_min_dis(mails, capacity, left);
        if (i) cout << endl;
        cout << min_distance << endl;
    }

    return 0;
}