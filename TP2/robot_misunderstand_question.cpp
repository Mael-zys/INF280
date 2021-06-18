#include <iostream>
#include <stdlib.h>
#include <vector>

using namespace std;

int capacity;

int find_min_point(vector<vector<int>> &v, int cap, vector<int> &s) {
    int min_dis = 65535;
    int min_index = -1;
    for(int i = 0; i < v.size(); i++) {
        int distance = abs(v[i][0] - s[0]) + abs(v[i][1] - s[1]);
        if(distance < min_dis && v[i][2] <= cap) {
            min_dis = distance;
            min_index = i;
        }
    }
    return min_index;
}

int fin_min_dis(vector<vector<int>> &v, int cap, vector<int> &pos_now) {
    int dis1 = 65535, dis2 = 65535, flag1 = 0, flag2 = 0;
    if(v.empty()) return pos_now[0] + pos_now[1];
    for(int i = 0; i < v.size(); i++) {
        if(v[i] == pos_now) {
            v.erase(v.begin() + i);
            break;
        }
    }
    // cout<<v.size()<<endl;
    int nearest_index = find_min_point(v, cap, pos_now);
    if(nearest_index != -1) {
        vector<int> nearest = v[nearest_index];
        flag1 = 1;
        vector<vector<int>> v1(v.begin(), v.end());
        // v1.erase(v1.begin() + nearest_index);
        dis1 = abs(nearest[0] - pos_now[0]) + abs(nearest[1] - pos_now[1]);
        dis1 += fin_min_dis(v1, cap - nearest[2], nearest);
        // cout<<dis1<<endl;
    }

    vector<int> init(3, 0);
    if (pos_now != init) {
        vector<vector<int>> v2(v.begin(), v.end());
        dis2 = (pos_now[0] + pos_now[1]);
        dis2 += fin_min_dis(v2, capacity, init);
        // cout<<dis2<<endl;
    }

    return min(dis1, dis2);
}

int main() {
    int num_case = 0;
    cin >> num_case;
    // cout << "cases: " << num_case <<endl;
    for(int i = 0; i < num_case; i++) {
        // int temp;
        // cin >> temp;
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
        vector<int> init(3, 0);
        int min_distance = fin_min_dis(mails, capacity, init);
        cout << min_distance << endl;
        cout << endl;
    }

    return 0;
}