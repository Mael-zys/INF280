#include<stdlib.h>
#include<iostream>
#include<vector>
#include<unordered_map>
#include<string>
#include<math.h>
#include<limits.h>
#include <algorithm>

using namespace std;

// calculate the min distance between each points and then return the max distance in this graph
int FloydWarshall(vector<vector<long>> &v) {
    int n = v.size();
    long max_dist = 0;
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                v[i][j] = min(v[i][j], v[i][k] + v[k][j]);
                if (k == n - 1) max_dist = max(max_dist, v[i][j]);
            }
        }
    }
    return max_dist;
}

int main() {
    int num_people, num_r;
    int count = 0;
    while (cin >> num_people >> num_r) {
        if (num_people == 0) break;
        count++;

        // read relations
        vector<vector<long>> dist(num_people, vector<long> (num_people, INT_MAX));
        unordered_map<string, int> index;
        string s1, s2;
        int i1, i2;
        for (int i = 0; i < num_r; i++) {
            cin >> s1 >> s2;
            if (index.count(s1) > 0) {
                i1 = index[s1];
            }
            else {
                i1 = index.size();
                index[s1] = i1;
                dist[i1][i1] = 0;
            }
            if (index.count(s2) > 0) {
                i2 = index[s2];
            }
            else {
                i2 = index.size();
                index[s2] = i2;
                dist[i2][i2] = 0;
            }
            dist[i1][i2] = dist[i2][i1] = 1;
        }

        // use floyd warshall to find max distance
        int max_dist = FloydWarshall(dist);

        if (max_dist == INT_MAX) cout << "Network " << count << ": DISCONNECTED"<< endl << endl;
        else cout << "Network " << count << ": "<< max_dist << endl << endl;
    }
    return 0;
}