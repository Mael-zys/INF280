#include<stdlib.h>
#include<iostream>
using namespace std;

int main() {
    int width, numCake, widthPiece, lengthPiece;
    while(cin >> width) {
        unsigned long long int surface = 0;
        cin >> numCake;
        for (unsigned long long int i = 0; i < numCake; i++) {
            cin >> widthPiece >> lengthPiece;
            surface += widthPiece * lengthPiece;
        }
        cout << surface / width << endl;
    }
    return 0;

}