# include<stdlib.h>
# include<iostream>
# include<cctype>

using namespace std;

// using the trick that if a number is multiple of 3, then the digits of this number will always add up to a multiple of 3

int main() {
    string s;
    while (cin >> s) {
        long long remainder[3] = {1, 0, 0};
        int acc = 0;
        long long nums = 0;
        for (int i = 0; i< s.size(); i++) {
            int temp = s[i] - '0';
            if (!isdigit(s[i])) {
                acc = 0;
                remainder[0] = 1;
                remainder[1] = remainder[2] = 0;
                continue;
            }
            else {
                acc = (acc + temp) % 3;
                nums += remainder[acc];
                remainder[acc]++;
            }
        }
        cout << nums << endl;
    }
    return 0;
}