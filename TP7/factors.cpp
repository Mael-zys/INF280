# include <stdlib.h>
# include <iostream>
# include <bitset>
# include <vector>
# include <cmath>
# include <unordered_map>

using namespace std;

// learn from:
// http://www.csc.kth.se/~austrin/icpc/finals2013solutions.pdf
// https://blog.csdn.net/weixin_30332241/article/details/96302648

vector<unsigned long long> premiers;

unsigned long long INF = 0x7FFFFFFFFFFFFFFFLL;

// from lecture slide
void cal_premier() {
    bitset<10000001> P;
    P.set(); // initialisation
    P[0] = P[1] = 0;
    for (int i = 2; i < 1e5; i++)
        if (P[i]) {
            for (int j=i*i; j < 1e5; j+=i)
                P[j]=0;
            premiers.push_back(i);
            if (premiers.size() == 62) return;
        }
}

// map from n to k
unordered_map<unsigned long long, unsigned long long> table;

unsigned long long C[63][63] = {0}; // combinaison
unsigned long long power[63] = {0};

void cal_c() {
    C[0][0] = 1;
    for (unsigned long long i = 1; i < 63; i++) {
        C[i][0] = 1;
        C[i][i] = 1;
        for (unsigned long long j = 1; j <= i/2; j++) {
            if ((INF / (i-j+1) < C[i][j-1])) break;
            C[i][j] = C[i][j-1] * (i-j+1)/j;
            
            C[i][i-j] = C[i][j];
            
            // cout << C[i][j] << endl;
        }
        // cout << i << endl;
    }
}


// unsigned long long cal_C(int sum, int j) {
//     unsigned long long product = 1, division = 1;
//     for (int i = sum - j + 1; i <= sum; i++) {
//         product *= i;
//     }
//     for (int i = 1; i <= j; j++) division *= i;
//     if (division == 0) return 0;
//     return product/division;
// }


void cal_possible_k(unsigned long long sum, unsigned long long index) {
    for (unsigned long long j = 1; j <= sum, j <= power[index-1]; j++) {
        power[index] = j;

        if (C[sum][j] == 0) return;
        if (j == sum) {
            unsigned long long n = 1;
            // cout << n << endl;
            unsigned long long sum_temp = 0;
            unsigned long long k = 1;
            for (unsigned long long i = 1; i <= index; i++) {
                sum_temp += power[i];

                // cout << sum_temp << " " << power[i] << endl;
                unsigned long long temp1 = C[sum_temp][power[i]], temp2 = pow(premiers[i-1], power[i]);
                if (INF / n < temp1 || INF / k < temp2) return;
                n *= temp1;
                k *= temp2;
                // if (k == 0 || n == 0 || k >= (1LLU<<63) || n >= (1LLU<<63)) return;
            }
            // cout << index << " " << j << " " << power[index - 1] << " " << n << " " << k << endl;
            if (table.count(n) == 0) table[n] = k;
            else table[n] = min(k, table[n]);

            
            return;
        }
        else cal_possible_k(sum - j, index+1);
    }
}

void build_table() {
    for (unsigned long long sum = 1; sum <= 62; sum++) { // pow sum

        cal_possible_k(sum, 1);
        // cout << sum << endl;
    }
}

int main() {
    long long n;
    power[0] = 100;
    cal_c();
    cal_premier();
    // for (int i = 0; i < 5; i++) {
    //     cout << premiers[i] << " ";
    // }
    // cout << endl;

    build_table();
    // cout << table.size() << endl;
    
    while (cin >> n) {
        if (n == 1) {
            cout << 1 << " " << 2 << endl;
            continue;
        }

        cout << n << " " << table[n] << endl;
    }
    return 0;
}