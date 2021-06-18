#include<stdlib.h>
#include<iostream>
#include<vector>
#include<queue>
#include<stack>

using namespace std;

// matching Hopcroft-Karp

#define inf 0x3f3f3f3f
#define Nil 0

vector<int> rMax, cMax, rPair, cPair, Dist;
vector<vector<int>> adj, graph;

void Initialization() {
    for (int i = 1; i < rMax.size(); i++) 
        for (int j = 1; j < cMax.size(); j++) 
            if (rMax[i] == cMax[j] && rMax[i] && graph[i-1][j-1]) 
                adj[i].push_back(j);
    return;
}

bool BFS() {
    queue<int> q;
    Dist[Nil] = inf;
    for (int i = 1; i < rMax.size(); i++) {
        if (rPair[i] == Nil) {
            Dist[i] = 0;
            q.push(i);
        }
        else Dist[i] = inf;
    }

    while (!q.empty()) {
        int x = q.front();
        q.pop();
        if (Dist[x] < Dist[Nil]) {
            for (auto & y : adj[x]) {
                if (Dist[cPair[y]] == inf) {
                    q.push(cPair[y]);
                    Dist[cPair[y]] = Dist[x] + 1;
                }
            }
        }
    }
    return Dist[Nil] != inf;
}

bool DFS(int node) {
    if (node == Nil) return true;
    for (auto & y : adj[node]) {
        if (Dist[cPair[y]] == Dist[node] + 1 && DFS(cPair[y])) {
            cPair[y] = node;
            rPair[node] = y;
            return true;
        }
    }
    return false;
}

void HopcroftKarp() {
    while(BFS()) {
        for (int i = 1; i < rMax.size(); i++) 
            if (rPair[i] == Nil) 
                DFS(i);
    }
}

int main() {
    int r, c;
    while (cin >> r >> c) {
        // initialisation
        rMax = vector<int> (r+1, 0);
        cMax = vector<int> (c+1, 0);
        adj = vector<vector<int>> (r+1);
        rPair = vector<int> (r + 1, Nil);
        cPair = vector<int> (c + 1, Nil);
        Dist = vector<int> (r + 1);
        graph = vector<vector<int>> (r, vector<int>(c, 0));
        long long num = 0;
        
        // read input
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                cin >> graph[i][j];
                if (graph[i][j] > rMax[i+1]) rMax[i+1] = graph[i][j];
                if (graph[i][j] > cMax[j+1]) cMax[j+1] = graph[i][j];
                if (graph[i][j] != 0) num += (graph[i][j] - 1);  // we first remove temp-1 crates in this pile
            }
        }

        // initialise adj
        Initialization();

        // HopcroftKarp
        HopcroftKarp();

        // calculate the max number
        for (int i = 1; i < rMax.size(); i++) {
            if (rMax[i] != 0) num -= rMax[i] - 1;
            cMax[rPair[i]] = 0;
        }
        for (int j = 1; j < cMax.size(); j++) {
            if (cMax[j] != 0) num -= cMax[j] - 1;
        }
        cout << num << endl;
    }
    return 0; 
}