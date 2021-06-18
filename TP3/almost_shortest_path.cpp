#include<stdlib.h>
#include<iostream>
#include<vector>
#include<limits.h>
#include<queue>
#include<utility>

using namespace std;

// calculate the min distance and the path between each S and D, and then return the min distance in this graph
int Dijkstra(vector<vector<int>> &v, vector<int> &dist, int S, int D) {
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
                dist[i] = temp;
                que.push(make_pair(dist[i], i));
            }
        }
    }

    return dist[D] >= INT_MAX ? -1: dist[D];
}

void remove_min_path(vector<vector<int>> &v, vector<int> &dist1, vector<int> &dist2, int min_dist) {
    for (int i = 0; i < v.size(); i++) {
        for (int j = 0; j < v.size(); j++) {
            if (v[i][j] == INT_MAX) continue;
            if (dist1[i] + dist2[j] + v[i][j] == min_dist) v[i][j] = INT_MAX;
        }
    }
}

int main() {
    int N, M;
    while (cin >> N >> M) {
        if (N == 0) break;

        int S, D;
        cin >> S >> D;

        // read roads
        vector<vector<int>> graph1(N, vector<int> (N, INT_MAX));
        vector<vector<int>> graph2(N, vector<int> (N, INT_MAX));
        int p1, p2, d;
        for (int i = 0; i < M; i++) {
            cin >> p1 >> p2 >> d;
            graph1[p1][p2] = d;
            graph2[p2][p1] = d;
        }
        
        vector<int> dist1(graph1.size(), INT_MAX);
        vector<int> dist2(graph1.size(), INT_MAX);
        
        // use Dijkstra to find min distance
        int min_dist = Dijkstra(graph1, dist1, S, D);
        int dis_temp = Dijkstra(graph2, dist2, D, S);
        
        // remove the road pass the min path
        remove_min_path(graph1, dist1, dist2, min_dist);
        
        // use Dijkstra to find new min distance
        vector<int> dist3(graph1.size(), INT_MAX);
        int new_dist = Dijkstra(graph1, dist3, S, D);

        cout << new_dist << endl;
    }
    return 0;
}