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

    // if p = "RPRRPR", then we construc s = "RPRRPRRPRRP". len(s) = 2*len(p) - 1
    string s = p;
    s.insert(s.end(), p.begin(), p.end()-1); 

    // construct the KMP table
    int np = p.size(), ns = s.size();
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
    cnd = 0; // position courante dans le motif p
    for (int i = 0; i <= ns; i++) { // tant qu'on ne lit pas
        while (cnd >= 0 && p[cnd] != s[i]) // le prochain char de p
            cnd = T[cnd]; // on recule dans p
        cnd++; // maintenant que le prochain char convient, avancer
        if (cnd == np) {
            // on a atteint la fin de p, donc on a trouvé un match

            // verify whether the overlop sequence is larger than 2*l-n
            if ( (2*np - i - 1) >= (2 * np - n))
                overlap[index].push_back(i - np + 1);

            // on recule dans p au cas où le prochain match chevauche
            cnd = T[cnd];
        }
    }
}

bool cmp (vector<int> a, vector<int> b) { 
    int i = a.size() - 1, j = b.size() - 1;
    while (i && j) {
        if (a[i] < b[j]) return true;
        else if (a[i] > b[j]) return false;
        i--;
        j--;
    }
    if (j == 0) return false; // if a == b or len(a) > len(b)
    else return true;
}

void test() {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < overlap[i].size(); j++) cout<< overlap[i][j]<< " ";
        cout<<endl;
    }
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
        test();
        // sort the overlap vectors
        stable_sort(overlap.begin(), overlap.end(), cmp);

        for (int i = 0; i < m; i++) {
            int index = overlap[i][0];
            cout << predictions[index] << endl;
        }
    }
    return 0;
}
