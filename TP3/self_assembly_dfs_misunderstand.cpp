//DFS to detect if a cycle exists

// wrong, the molecule may be rotated and reected, here I only consider the ratation case.

#include<stdlib.h>
#include<iostream>
#include<vector>
#include<unordered_map>
#include<string>
#include<stack>
#include<stdio.h>
#include<map>
using namespace std;

class Molecule {
    public:
        string left;
        string up;
        string right;
        string down;
        int horizontalPos;
        int verticalPos;
        int moleculeIndex;

        //initialisation
        Molecule(string lt=NULL, string ut=NULL, string rt=NULL, string dt=NULL, int hp=0, int vp=0, int mt=0){
            left = lt;
            right = rt;
            up = ut;
            down = dt;
            horizontalPos = hp;
            verticalPos = vp;
            moleculeIndex = mt;
        }
        
        // for the hash function
        bool operator==(const Molecule & m) const
        {
            return left.compare(m.left) == 0 && right.compare(m.right) == 0 && up.compare(m.up) == 0 && down.compare(m.down) == 0;
        }
};

struct VectorHasher {
    int operator()(const vector<int> &V) const {
        int hash = V.size();
        for(auto &i : V) {
            hash ^= i + 0x9e3779b9 + (hash << 6) + (hash >> 2);
        }
        return hash;
    }
};

class MoleculeGroup {
    public:
        unordered_map<vector<int>, Molecule*, VectorHasher> group; // contain position of the molecules
        vector<vector<string>> moleculeType;  //each molecule has 4 types of connection
        unordered_map<string, vector<int>> index;  //key is one type of connection, value is an array of molecule index
        
        stack<Molecule*> s;
        // vector<bool> inStack;
        map<Molecule*, int> inStack;
        bool repeat = false;
        int num = 0;

        // if 2 label can connect
        bool connectable(string connectorLabel1, string connectorLabel2) {
            return connectorLabel1[0] == connectorLabel2[0] && connectorLabel1[1] != connectorLabel2[1];
        }

        // if this label can be connected, if so change the label
        bool connectableLabel(string &connectorLabel) {
            if (connectorLabel[1] == '+') {
                connectorLabel[1] = '-';
                return true;
            }
            if (connectorLabel[1] == '-') {
                connectorLabel[1] = '+';
                return true;
            }
            return false;
        }

        // try to connect Molecule in position (ht, vt) with connectorLabel
        bool connectMolecule(int ht, int vt, string connectorLabel, int direction) {
            if (index.count(connectorLabel) > 0) {
                for (auto & i : index[connectorLabel]) {
                    int j;
                    for (j = 0; j < 4; j++) {
                        if (moleculeType[i][j] == connectorLabel) break;
                    }
                    Molecule *m = new Molecule(moleculeType[i][(direction + j) % 4], moleculeType[i][(direction + j + 1) % 4], moleculeType[i][(direction + j + 2) % 4], moleculeType[i][(direction + j + 3) % 4], ht, vt, i);
                    printf("%d\n",2);
                    if (group.count(vector<int> ({ht - 1, vt})) > 0) {
                        printf("%d\n",3);
                        if (!connectable(m->left, (group[vector<int>({ht - 1, vt})])->right)) continue;        
                    }
                    if (group.count(vector<int> ({ht + 1, vt})) > 0) {
                        printf("%d\n",4);
                        if (!connectable(m->right, (group[vector<int>({ht + 1, vt})])->left)) continue;        
                    }
                    if (group.count(vector<int> ({ht, vt - 1})) > 0) {
                        printf("%d\n",5);
                        if (!connectable(m->down, (group[vector<int>({ht, vt - 1})])->up)) continue;        
                    }
                    if (group.count(vector<int> ({ht, vt + 1})) > 0) {
                        printf("%d\n",6);
                        if (!connectable(m->up, (group[vector<int>({ht, vt + 1})])->down)) continue;        
                    }
                    // if (inStack[i] == true) repeat = true;
                    // inStack[i] = true;
                    if (inStack[m] == 1) repeat = true;
                    inStack[m] = 1;
                    group[vector<int> ({ht, vt})] = m;
                    printf("%d\n",7);
                    return true;
                }
            }
            return false;
        }

        //DFS
        bool DFS(int node) {
            Molecule* root = new Molecule(moleculeType[node][0], moleculeType[node][1], moleculeType[node][2], moleculeType[node][3], 0, 0, node);
            s.push(root);
            printf("%d\n",-3);
            group[vector<int> ({0, 0})] = root;
            printf("%d\n",-4);
            while (!s.empty()) {
                Molecule* temp = s.top();
                s.pop();
                if (repeat || num > 4) return true;
                string lt = temp->left;
                printf("%d\n",-1);
                if (connectableLabel(lt)) {
                    if (connectMolecule(temp->horizontalPos - 1, temp->verticalPos, lt, 2)) {
                        printf("%d\n",9);
                        Molecule *a = group[vector<int> ({temp->horizontalPos - 1, temp->verticalPos})];
                        printf("%d\n",10);
                        s.push(a);
                        if (moleculeType.size() == 1) num++;
                    }
                }
                printf("%d\n",-2);
                string ut = temp->up;
                if (connectableLabel(ut)) {
                    if (connectMolecule(temp->horizontalPos, temp->verticalPos + 1, ut, 3)) {
                        s.push(group[vector<int> ({temp->horizontalPos, temp->verticalPos + 1})]);
                        if (moleculeType.size() == 1) num++;
                    }
                }
                string rt = temp->right;
                if (connectableLabel(rt)) {
                    if (connectMolecule(temp->horizontalPos + 1, temp->verticalPos, rt, 0)) {
                        s.push(group[vector<int> ({temp->horizontalPos + 1, temp->verticalPos})]);
                        if (moleculeType.size() == 1) num++;
                    }
                }
                string dt = temp->down;
                if (connectableLabel(dt)) {
                    if (connectMolecule(temp->horizontalPos, temp->verticalPos - 1, dt, 1)) {
                        s.push(group[vector<int> ({temp->horizontalPos, temp->verticalPos - 1})]);
                        if (moleculeType.size() == 1) num++;
                    }
                }
                // inStack[temp->moleculeIndex] = false;
                inStack[temp] = 0;
            }
            return false;
        }

};




int main() {
    int num_type;
    while (cin >> num_type) {
        MoleculeGroup MG;
        
        // read types
        string tmp;
        for (int i = 0; i < num_type; i++) {
            cin >> tmp;
            vector<string> tempString;
            for (int j = 0; j < 4; j++) {
                string tmp1(tmp, 2 * j, 2);
                MG.index[tmp1].push_back(i);
                tempString.push_back(tmp1);
            }
            MG.moleculeType.push_back(tempString);
        }
        
        // DFS
        // MG.inStack = vector<bool> (num_type, false);
        int flag = 0;
        for (int i = 0; i < num_type; i++) {
            if (MG.DFS(i)) {
                cout << "unbounded" << endl;
                flag = 1;
                break;
            }
        }
        if (flag == 0) cout << "bounded" << endl;
    }
    return 0;
}