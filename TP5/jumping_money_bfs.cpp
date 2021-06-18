# include<stdlib.h>
# include<iostream>
# include<queue>

using namespace std;
const int N = 22;
int shoot_point[1<<N], pre_state[1<<N];
bool visit[1<<N];
vector<int> adj[N];

// using bit operation to reduce time

// bfs to find the shorest path from init_state to 0
bool bfs(int init, int num_tree) {
    queue<int> q;
    q.push(init);
    visit[init] = true;

    while(!q.empty()) {
        int state = q.front();
        q.pop();

        // if state == 0, means the monkey has no where to hide
        if (!state) return true; 

        // shooting position.  list from 0 to num_tree to ensure lexicographical order
        for (int i = 0; i < num_tree; i++) {
            int next_state = 0; // the monkey state after the shoot

            // possible position for monkey
            for (int j = 0; j < num_tree; j++) {
                if (j != i && (state & (1<<j))) { //if the monkey can be possible to hide in j
                    for (int k = 0; k < adj[j].size(); k++) {
                        next_state = next_state | (1<<(adj[j][k]));
                    }
                }
            }

            // if we have visited this state
            if (visit[next_state]) continue;

            q.push(next_state);
            pre_state[next_state] = state;
            visit[next_state] = true;
            shoot_point[next_state] = i;
        }
    }
    return false;
}


int main() {
    int num_tree, num_adj;
    while (cin >> num_tree >> num_adj && num_tree) {
        // at begining, the monkey can be in any tree
        int initial_state = (1<<num_tree) -1;

        // initialize visit state
        for (int i = 0; i < initial_state; i++) {
            visit[i] = false;
        }

        // initialize adj
        for (int i = 0; i < num_tree; i++) {
            adj[i].clear();
        }

        //read adj information
        int a,b;
        for (int i = 0; i < num_adj; i++) {
            cin >> a >> b;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }

        if (bfs(initial_state, num_tree)) {
            int state = 0;
            vector<int> shoot_order;
            // trace back to save the order
            while (state != initial_state) {
                shoot_order.push_back(shoot_point[state]);
                state = pre_state[state];
            }
            cout << shoot_order.size() << ":";
            for (int i = shoot_order.size() - 1; i >=0; i--) {
                cout << " " << shoot_order[i];
            }
            cout << endl;
        }
        else {
            cout << "Impossible" << endl;
        }
    }
    return 0;
}