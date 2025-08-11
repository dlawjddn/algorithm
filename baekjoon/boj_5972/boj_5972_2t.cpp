#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

#define INF 987654321

using namespace std;

int node_cnt, edge_cnt;
vector<vector<pair<int, int> > > maps;
vector<int> visited;

void dijkstra() {
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
    pq.push({0, 1});
    visited[1] = 0;

    while(!pq.empty()) {
        auto[cost, node] = pq.top(); pq.pop();
        if (visited[node] != cost) continue;
        for(int x=0; x<maps[node].size(); x++) {
            auto[nnode, add_cost] = maps[node][x];
            int ncost = cost + add_cost;
            if (visited[nnode] <= ncost) continue;
            pq.push({ncost, nnode});
            visited[nnode] = ncost;
        }
    }
}

int main() {
    cin>>node_cnt>>edge_cnt;
    maps.resize(node_cnt + 1);
    visited.resize(node_cnt + 1, INF);

    for(int i=0; i<edge_cnt; i++) {
        int node1, node2, cost; cin>>node1>>node2>>cost;
        maps[node1].push_back({node2, cost});
        maps[node2].push_back({node1, cost});
    }

    dijkstra();
    cout<<visited[node_cnt];
}