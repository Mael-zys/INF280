#include<stdlib.h>
#include<iostream>
#include<vector>
#include<limits.h>
#include<queue>
#include<utility>

using namespace std;

// calculate the min distance and the path between each S and D, and then return the min distance in this graph
int Dijkstra(vector<vector<int>> &v, vector<int> &path, int S, int D) {
    vector<int> dist(v.size(), INT_MAX);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> que;
    dist[S] = 0;
    que.push(make_pair(0, S));
    while (!que.empty()) {
        int t = que.top().second;
        que.pop();
        if (t == D) break;

        for (int i = 0; i < v[t].size(); i++) {
            if (v[t][i] == INT_MAX) continue;
            int temp = dist[t] + v[t][i];

            if (temp < dist[i]) {
                path[i] = t;
                dist[i] = temp;
                que.push(make_pair(dist[i], i));
            }
        }
    }

    return dist[D] >= INT_MAX ? -1: dist[D];
}

void remove_min_path(vector<vector<int>> &v, vector<int> &path, int S, int D) {
    for (int i = path[D], j = D; i != -1; j = i, i = path[i]) {
        v[i][j] = INT_MAX;
    }
}

int main() {
    int N, M;
    while (cin >> N >> M) {
        if (N == 0) break;

        int S, D;
        cin >> S >> D;

        // read roads
        vector<vector<int>> dist(N, vector<int> (N, INT_MAX));
        int p1, p2, d;
        for (int i = 0; i < M; i++) {
            cin >> p1 >> p2 >> d;
            dist[p1][p2] = d;
        }

        vector<int> minPath(dist.size(), -1);
        
        // use Dijkstra to find min distance and the path
        int min_dist = Dijkstra(dist, minPath, S, D);
        
        int new_dist;
        do {

            remove_min_path(dist, minPath, S, D); 
            minPath = vector<int>(dist.size(), -1);
            new_dist = Dijkstra(dist, minPath, S, D);
        } while (new_dist == min_dist);

        cout << new_dist << endl;
    }
    return 0;
}