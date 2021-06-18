#include<iostream>
#include<stdlib.h>
#include<deque>

using namespace std;

int main(){
    int numCase = 1, P, C;
     
    while (cin >> P >> C) {
        if (P == 0) return 0; 
        cout << "Case "<<numCase<<":"<<endl;
        numCase += 1;
        P = min(C, P);
        deque<int> Queue;
        for (int i = 0; i < P; i++) {
            Queue.push_back(i+1);
        }
        for (int i = 0; i < C; i++) {
            char Command;
            cin >> Command;
            if (Command == 'N') {
                cout<<Queue.front()<<endl;
                Queue.push_back(Queue.front());
                Queue.pop_front();
            }
            else if (Command == 'E') {
                int emergency;
                cin >> emergency;
                for (int j = 0; j < Queue.size(); j++) {
                    if (*(Queue.begin() + j) == emergency)
                        Queue.erase(Queue.begin() + j);
                }
                Queue.push_front(emergency);
            }
        }
    }
    return 0;
}