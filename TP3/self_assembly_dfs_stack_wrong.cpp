//DFS to detect if a cycle exists

#include<stdlib.h>
#include<iostream>
#include<vector>
#include<unordered_map>
#include<string>
#include<stack>
#include<unordered_set>
using namespace std;

//change the molecule type from string to int, if t = A+, change it to 0, t = A-, change it to 1;
int moleculeType(string t) {
    return 2 * (t[0] - 'A') + int (t[1] == '-'); 
}

// build graph
void buildGraph (vector<int> v, unordered_map<int, unordered_set<int>> &graph) {
    for (int i = 0; i < v.size(); i++) {
        for (int j = 0; j < v.size(); j++) {
            if (i != j) graph[v[i]].insert(v[j]^1);
        }
    }
}

// dfs to detect cycle
bool dfs(unordered_map<int, unordered_set<int>> &graph) {
    
    unordered_map<int, int> visit;

    for (auto node = graph.begin(); node != graph.end(); node++) {
        int i = node->first;
        if (visit[i] == 1) continue;

        stack<int> s;
        s.push(i);
        while (!s.empty()) {
            i = s.top();

            if (visit.count(i) == 0) visit[i] = 2;
            else {
                visit[i] = 1; //visited
                s.pop();
            }

            for (auto &j : graph[i]) {                
                if (visit[j] == 2) return true;
                s.push(j);   
            }
        }
    }
    return false;
}

int main() {
    int num_type;
    while (cin >> num_type) {
        
        // max num_type is 4000, so I think we cannot use a matrix to store the graph, instead, we use a list
        unordered_map<int, unordered_set<int>> graph;
        
        
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
            buildGraph(tempType, graph);
        }
        
        // DFS
        if (dfs(graph)) cout << "unbounded" << endl;
        else cout << "bounded" << endl;
    }
    return 0;
}
