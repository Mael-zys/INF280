# include<stdlib.h>
# include<iostream>
# include<vector>

using namespace std;

// using the trick that if a number is multiple of 3, then the digits of this number will always add up to a multiple of 3
// the main idea is brute force

vector<int> dp;

int main() {
    string s;
    while (cin >> s) {
        dp.clear();
        long long nums = 0;
        for (int i = 0; i < s.size(); i++) {
            int temp = s[i] - '0';
            if (temp < 0 || temp > 9) {
                dp.clear();
                continue;
            }
            temp %= 3;
            int remainder = temp;
            if (remainder == 0) nums++;
            for (int j = dp.size() - 1; j >= 0; j--) {
                remainder += dp[j];
                remainder %= 3;
                if (remainder == 0) nums++;
            }
            dp.push_back(temp);
        }
        cout << nums << endl;
    }
    return 0;
}