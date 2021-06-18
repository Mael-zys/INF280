#include<stdlib.h>
#include<iostream>
#include<unordered_map>
#include<vector>
using namespace std;

unordered_map<int, vector<int>> sets;

int findRoot(int x) {
    if (sets[x][0] == x) return x;
    else return findRoot(sets[x][0]);
}

bool Union(int x, int y) {
    int a = findRoot(x);
    int b = findRoot(y);
    if (a == b) return false;  // cycle in this tree
    if (sets[a][1] > sets[b][1]) sets[b][0] = a;
    else sets[a][0] = b;
    if (sets[a][1] == sets[b][1]) sets[b][1]++;
    return true;
}

int main() {
    int a, b, num = 0;
    while (cin >> a) {
        if (a != -1) {
            cin >> b;
            if (sets.count(a) == 0) sets[a] = vector<int> ({a, 0});
            if (sets.count(b) == 0) sets[b] = vector<int> ({b, 0});
            if (!Union(a,b)) num++;
        }
        if (a == -1) {
            cout << num <<endl;
            num = 0;
            sets.clear();
        }
    }
    return 0; 
}