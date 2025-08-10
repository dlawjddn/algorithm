#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int letter_cnt, snake_cnt, dice[6] = {1,2,3,4,5,6};
vector<int> shortcut(101, 0);
vector<int> visited(101, -1);

void solve() {
    queue<pair<int, int> > q;
    q.push({1, 0});
    visited[1] = 0;
    while(!q.empty()) {
        auto[pos, cnt] = q.front(); q.pop();
        for(int d=0; d<6; d++) {
            int npos = pos + dice[d];
            int ncnt = cnt + 1;
            if (npos > 100 || visited[npos] != -1) continue;
            if (shortcut[npos] != 0) {
                visited[npos] = ncnt;
                npos = shortcut[npos];
            }
            q.push({npos, ncnt});
            visited[npos] = ncnt;
        }
    }
}

int main() {
    cin>>letter_cnt>>snake_cnt;
    for(int i=0; i<letter_cnt; i++) {
        int s, t; cin>>s>>t;
        shortcut[s] = t;
    }
    for(int i=0; i<snake_cnt; i++) {
        int s, t; cin>>s>>t;
        shortcut[s] = t;
    }
    solve();
    cout<<visited[100];
}