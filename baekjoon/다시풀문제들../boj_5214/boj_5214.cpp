#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

#define INF 987654321

using namespace std;

struct Info {
    bool tube;
    int pos, cost;
    bool operator<(Info other) const {
        return cost > other.cost;
    }
};
int node_cnt, tube_connected, tube_cnt;
vector<vector<int> > maps;
vector<vector<int> > tubes;
vector<int> visited;

void bfs() {
    queue<Info> q;
    q.push({false, 1, 1});
    visited[1] = 1;
    while(!q.empty()) {
        auto[tube, pos, cost] = q.front(); q.pop();
        if (tube) {
            for(int x=0; x<tubes[pos].size(); x++) {
                int npos = tubes[pos][x];
                int ncost = cost + 1;
                if (visited[npos] != INF) continue;
                q.push({false, npos, ncost});
                visited[npos] = ncost;
            }
        }
        else {
            for(int x=0; x<maps[pos].size(); x++) {
                int ntube = maps[pos][x];
                int ncost = cost;
                q.push({true, ntube, ncost});
            }
        }
    }
}

int main() {
    cin>>node_cnt>>tube_connected>>tube_cnt;
    maps.resize(node_cnt + 1);
    visited.resize(node_cnt + 1, INF);
    for(int i=0; i<tube_cnt; i++) {
        vector<int> temp_tube;
        for(int j=0; j<tube_connected; j++) {
            int node; cin>>node;
            maps[node].push_back(i);
            temp_tube.push_back(node);
        }
        tubes.push_back(temp_tube);
    }
    bfs();
    cout<<((visited[node_cnt] == INF) ? -1 : visited[node_cnt]);
}