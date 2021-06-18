# include <stdlib.h>
# include <iostream>
# include <vector>

using namespace std;

// my idea:
// https://drive.google.com/drive/folders/1EbknrYXeGm-WeoeAKiWTjCdoGpOoNZ-k?usp=sharing

vector<int> bits_one;

void find_position_bit_one(long num) {
    int i = 0;
    while (num) {
        if (num & 1) bits_one.push_back(i);
        num = num >> 1;
        i++;
    }
}

// num = n*2^(n-1)
long long calculate_one_from_zero_for_power_two(int n) {
    return n*(1LL<<(n-1));
}

long long calculate_one_from_zero() {
    long long num_one = 0;
    for (int i = bits_one.size() - 1, j = 0; i >=0; i--, j++) {
        num_one += calculate_one_from_zero_for_power_two(bits_one[i]) + j * (1LL << bits_one[i]);
    }
    num_one += bits_one.size();
    return num_one;
}

int main() {
    long num1, num2;
    while (cin >> num1 >> num2) {
        bits_one.clear();
        find_position_bit_one(num1 - 1);
        long long min_num = calculate_one_from_zero();

        bits_one.clear();
        find_position_bit_one(num2);
        long long max_num = calculate_one_from_zero();

        cout << max_num - min_num << endl;
    }
    return 0;
}