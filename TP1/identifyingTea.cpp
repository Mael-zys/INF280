#include <iostream>
#include <stdlib.h>
using namespace std;
int main() {
    int answer;
    int num[5];
    while (cin >> answer) {
        cin >> num[0] >> num[1] >> num[2] >> num[3] >> num[4];
        int correctNum = 0;
        for (int i = 0; i < 5; i++) {
            if (num[i] == answer)
                correctNum++;
        }
        cout << correctNum << endl;
    }
    return 0;
}