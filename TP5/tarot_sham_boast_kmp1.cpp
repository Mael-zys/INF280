# include<stdlib.h>
# include<iostream>
# include<vector>
# include<cstring>
# include<algorithm>

using namespace std;

/*
http://www.csc.kth.se/~austrin/icpc/finals2017solutions.pdf

Find the overlap sequence whose lenth >= 2*l - n. 
The lexicographically smaller overlap sequences leads to larger probabilities
We can use KMP method to find the sequence.
*/

int n, m;
vector<string> predictions;
vector<vector<int>> overlap; // the first index save the prediction index

// code modified from our lecture slide
void KMP(int index) {
    string p = predictions[index]; 

    // construct the KMP table
    int np = p.size();
    int T[np + 1];
    T[0] = -1;
    int cnd = 0;
    for (int i = 1; i <= np; i++) {
        T[i] = cnd;
        while (cnd >= 0 && p[cnd] != p[i])
            cnd = T[cnd];
        cnd++;
    }

    // find the sequence
    // back trace from the KMP table
    // example
    //  index       0 1 2 3 4 5 6
    //  string        P R P R P R
    //  T           0 0 0 1 2 3 4
    cnd = np; 
    cnd = T[cnd];
    while (cnd > 0) {
        if ( cnd >= (2 * np - n))
            overlap[index].push_back(cnd);
        cnd = T[cnd]; 
    }
}

bool cmp (vector<int> a, vector<int> b) { 
    int i;
    if (a.size() == 1 && b.size() == 1) return false;
    for (i=1; i<a.size() && i<b.size(); i++) {
        if (a[i] < b[i]) return true;
        else if (a[i] > b[i]) return false;
    }
    if (i == b.size()) return false;
    else return true; 
}

int main(){
    while(cin >> n >> m) {
        // initialize
        predictions.clear();
        overlap = vector<vector<int>>(m);
        string temp;
        
        // read input
        for (int i = 0; i < m; i++) {
            cin >> temp;
            predictions.push_back(temp);
            overlap[i].push_back(i);
            KMP(i);
        }

        // sort the overlap vectors
        stable_sort(overlap.begin(), overlap.end(), cmp);

        for (int i = 0; i < m; i++) {
            int index = overlap[i][0];
            cout << predictions[index] << endl;
        }
    }
    return 0;
}
