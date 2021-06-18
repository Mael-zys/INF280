#include<stdlib.h>
#include<iostream>
#include<map>
#include<stack>
#include<set>
#include<vector>
using namespace std;

// Use eulerian circuit. each node should have even degrees
// implementation is similar to Eulerian Paths talked in course.

map<int, map<int, int>> graph;
map<int, int> degree;

// verify whether each node has even degree (weights)
bool isCircuit() {
    for (map<int, int>::iterator i = degree.begin(); i != degree.end(); i++) {
        if (i->second % 2 != 0) {
            cout << "some beads may be lost" << endl;
            return false;
        }
    }
    return true;
}

// find the path
void eulerianCircuit() {
    int node = graph.begin() -> first;
    int lastNode = -1;
    stack<int> s;
    s.push(node);
    while (!s.empty()) {
        node = s.top();
        if (graph[node].empty()) {
            if (lastNode != -1) cout << lastNode << " " << node << endl;
            lastNode = node;
            s.pop();
        }
        else {
            int temp = graph[node].begin() -> first;
            s.push(temp);            
            graph[node][temp]--;
            graph[temp][node]--;
            if (graph[node][temp] == 0) graph[node].erase(temp);
            if (graph[temp][node] == 0) graph[temp].erase(node);
        }
    }
    return;
}

int main() {
    int numCase, numBeads;
    cin >> numCase;
    for (int k = 0; k < numCase; k++) {
        cin >> numBeads;
        int a, b;
        graph.clear();
        degree.clear();
        //read input
        for (int i = 0; i < numBeads; i++) {
            cin >> a >> b;
            graph[a][b]++;
            graph[b][a]++;
            degree[a]++;
            degree[b]++;
        }

        cout << "Case #" << k+1 << endl;
        if (isCircuit()) eulerianCircuit();
        if (k != numCase - 1) cout << endl;
    }
    return 0; 
}