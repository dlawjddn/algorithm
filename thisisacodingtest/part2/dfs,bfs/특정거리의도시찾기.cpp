#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

#define INF 987654321

using namespace std;

int node_cnt, edge_cnt, target, snode;
vector<vector<int> > maps;
vector<int> visited;

void init() {
    maps.resize(node_cnt + 1);
    visited.resize(node_cnt + 1, INF);
}

vector<int> dijkstra() {
    vector<int> result;
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
    pq.push({0, snode});
    visited[snode] = 0;
    while(!pq.empty()) {
        auto[cost, node] = pq.top(); pq.pop();
        if (visited[node] < cost) continue;
        for(int x=0; x<maps[node].size(); x++) {
            int nnode = maps[node][x];
            int ncost = cost + 1;
            if (visited[nnode] < ncost) continue;
            pq.push({ncost, nnode});
            visited[nnode] = ncost;
        }
    }
    for(int i=0; i<visited.size(); i++) {
        if (visited[i] == target) result.push_back(i);
    }
    return result;
}

int main() {
    cin>>node_cnt>>edge_cnt>>target>>snode;
    init();
    for(int i=0; i<edge_cnt; i++) {
        int from, to; cin>>from>>to;
        maps[from].push_back(to);
    }
    vector<int> answer = dijkstra();
    if (answer.size() == 0) {
        cout<<-1;
        return 0;
    }
    for(int i=0; i<answer.size(); i++) cout<<answer[i]<<' ';

}