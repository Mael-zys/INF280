# include <stdlib.h>
# include <iostream>
# include <bitset>
# include <vector>
# include <cmath>
# include <cstring>

using namespace std;

// my idea:
// https://drive.google.com/drive/folders/1EbknrYXeGm-WeoeAKiWTjCdoGpOoNZ-k?usp=sharing

vector<int> premiers;

// from lecture slide
void cal_premier() {
    bitset<10000001> P;
    P.set(); // initialisation
    P[0] = P[1] = 0;
    for (int i = 2; i < 1e3; i++)
        if (P[i]) {
            for (int j=i*i; j < 1e3; j+=i)
                P[j]=0;
            premiers.push_back(i);
        }
}

vector<int> factors;
vector<int> count;

void find_factors(long long n) {
    int j = 0;
    for (int i = 0; i < premiers.size(), n != 1; i++) {
        while (n % premiers[i] == 0) {
            if (factors.size() == j) factors.push_back(premiers[i]);
            if (count.size() == j) count.push_back(1);
            else count[j]++;
            n /= premiers[i];
        }
        j = factors.size();
    }
}

// unsigned long long find_arrangement(unsigned long long n) {
//     int size = factors.size();
//     unsigned long long pk = factors[size - 1];
//     unsigned long long qk = count[size - 1];
//     unsigned long long pqk = pow(pk, qk);
//     unsigned long long n1 = n / pqk;

//     vector<unsigned long long> arrangement(pqk);
//     arrangement[0] = 1;
//     for (unsigned long long i = 1; i < pqk; i++) {
//         arrangement[i] = arrangement[i-1]*i;
//         // cout << i << " " << arrangement[i] << endl;
//     }

//     unsigned long long count = pqk, j = pqk-1;
//     unsigned long long temp = arrangement[pqk - 1];

//     vector<unsigned long long> ij;
//     cout << temp << endl;
//     if ((temp / arrangement[j]) % n1);
//     while (count != 0) {
//         if (temp % arrangement[j] == 0 && temp / arrangement[j] % n1 == 0) {
//             temp /= arrangement[j];
//             ij.push_back(j);
//             count -= j;
//             j = min(count,j);
//         }
//         else j--;
//     }

//     unsigned long long res = 1;
//     for (int i = 0; i < ij.size(); i++) {
//         unsigned long long premier = premiers[i];
//         cout << premier << " " << ij[i] << endl;
//         res *= pow(premier, ij[i]);
//     }
//     return res;
// }

vector<__int128> arrangement(2, __int128(1));

unsigned long long find_arrangement(unsigned long long n) {
    int size = factors.size();
    unsigned long long pk = factors[size - 1];
    unsigned long long qk = count[size - 1];
    unsigned long long pqk = pk;
    // cout << pqk << endl;
    if (pqk >= arrangement.size()) {
        for (unsigned long long i = arrangement.size(); i <= pqk; i++) {
            arrangement.push_back(arrangement[i-1]*__int128(i));
        }
    }

    unsigned long long count = pqk, j = pqk-1;
    __int128 temp = arrangement[pqk];
    // cout << temp << endl;
    while (temp % n != 0) {
        count++;
        j++;
        // cout << count << endl;
        if (count >= arrangement.size()) arrangement.push_back(arrangement[j]*count);
        temp = arrangement[count];
    }

    vector<unsigned long long> ij;
    // cout << string(temp) << endl;

    while (count != 0) {
        // cout << j << endl;
        // cout << temp << " " << arrangement[j] << " " << n << endl;
        if ((temp / arrangement[j]) % __int128(n) == __int128(0)) {
            temp /= arrangement[j];
            ij.push_back(j);
            count -= j;
            // cout<<j<<endl;
            j = min(count,j);
        }
        else if (j > 1) j--;
    }

    unsigned long long res = 1;
    for (int i = 0; i < ij.size(); i++) {
        unsigned long long premier = premiers[i];
        // cout << premier << " " << ij[i] << endl;
        res *= pow(premier, ij[i]);
    }
    return res;
}

void test() {
    for (int i = 0; i < factors.size(); i++)
        cout << factors[i] << " " << count[i] << endl;
}

int main() {
    long long n;
    cal_premier();

    while (cin >> n) {
        if (n == 1) {
            cout << 1 << " " << 2 << endl;
            continue;
        }
        factors.clear();
        count.clear();
        find_factors(n);
        // test();
        cout << n << " " << find_arrangement(n) << endl;
    }
    return 0;
}