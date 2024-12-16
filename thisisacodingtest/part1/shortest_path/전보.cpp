#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

#define INF 987654321

using namespace std;

int node_cnt, edge_cnt, start;
vector<vector<pair<int, int> > > maps;
vector<int> visited;

void dijkstra() {
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
    pq.push({0, 1});
    visited[1] = 0;
    while(!pq.empty()) {
        auto[cost, node] = pq.top(); pq.pop();
        if (visited[node] != cost) continue;
        for(int d=0; d<maps[node].size(); d++) {
            int nnode = maps[node][d].first;
            int ncost = cost + maps[node][d].second;
            if (visited[nnode] <= ncost) continue;
            pq.push({ncost, nnode});
            visited[nnode] = ncost;
        }
    }
}

int main() {
    cin>>node_cnt>>edge_cnt>>start;
    maps.resize(node_cnt + 1);
    visited.resize(node_cnt + 1, INF);
    for(int i=0; i<edge_cnt; i++) {
        int snode, enode, cost; cin>>snode>>enode>>cost;
        maps[snode].push_back({enode, cost});
    }
    dijkstra();
    int answer_cnt = 0, answer_time = 0;
    for(int i=1; i<=node_cnt; i++) {
        if (visited[i] == INF) continue;
        answer_cnt ++;
        answer_time = max(answer_time, visited[i]);
    }
    cout<<answer_cnt - 1<<' '<<answer_time<<"\n";
}