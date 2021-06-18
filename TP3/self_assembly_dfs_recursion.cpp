//DFS to detect if a cycle exists

#include<stdlib.h>
#include<iostream>
#include<vector>
#include<string>
#include<memory.h>

using namespace std;

int graph[52][52];
int visit[52];

//change the molecule type from string to int, if t = A+, change it to 0, t = A-, change it to 1;
int moleculeType(string t) {
    return 2 * (t[0] - 'A') + int (t[1] == '-'); 
}

// build graph
void buildGraph (vector<int> v) {
    for (int i = 0; i < v.size(); i++) {
        for (int j = 0; j < v.size(); j++) {
            if (i != j) graph[v[i]][v[j]^1] = 1;
        }
    }
}

// dfs to detect cycle
bool dfs(int i) {
    visit[i] = 2; // in stack
    for (int j = 0; j < 52; j++) {
        if (graph[i][j] == 0) continue; 
        if (visit[j] == 2) return true;
        else if (visit[j] != 1 && dfs(j)) return true;
    }
    visit[i] = 1; // visited
    return false;
}

int main() {
    int num_type;
    while (cin >> num_type) {
        memset(graph, 0, sizeof graph);
        memset(visit, 0, sizeof visit);
        
        // read types
        string tmp;
        for (int i = 0; i < num_type; i++) {
            cin >> tmp;
            vector<int> tempType;
            for (int j = 0; j < 4; j++) {
                string tmp1(tmp, 2 * j, 2);
                // '00' is a dead end, we don't use it
                if (tmp1[0] != '0') tempType.push_back(moleculeType(tmp1));
            }
            buildGraph(tempType);
        }
        
        // DFS
        int flag = 0;
        for (int i = 0; i < 52; i++) {
            if (visit[i] != 1 && dfs(i)) {
                cout << "unbounded" << endl;
                flag = 1;
                break;
            }
        }
        if (!flag) cout << "bounded" << endl;
    }
    return 0;
}
