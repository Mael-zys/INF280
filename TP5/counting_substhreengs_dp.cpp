# include<stdlib.h>
# include<iostream>

using namespace std;

// using the trick that if a number is multiple of 3, then the digits of this number will always add up to a multiple of 3

int main() {
    string s;
    while (cin >> s) {
        long long remainder[3] = {0};
        long long nums = 0;
        for (int i = 0; i< s.size(); i++) {
            int temp = s[i] - '0';
            if (temp < 0 || temp > 9) {
                remainder[0] = remainder[1] = remainder[2] = 0LL;
                continue;
            }
            temp %= 3;
            if (temp == 0) {
                remainder[0]++;
            }
            else if (temp == 1) {
                int temp1 = remainder[1];
                remainder[1] = remainder[0] + 1;
                remainder[0] = remainder[2];
                remainder[2] = temp1;
            }
            else {
                int temp1 = remainder[2];
                remainder[2] = remainder[0] + 1;
                remainder[0] = remainder[1];
                remainder[1] = temp1;
            }
            nums += remainder[0];
        }
        cout << nums << endl;
    }
    return 0;
}