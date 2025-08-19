#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

#define INF 987654321

using namespace std;

int node_cnt, edge_cnt, party_pos;
vector<vector<pair<int, int> > > maps;
vector<vector<int> > costs;

vector<int> dijkstra(int snode) {
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
    vector<int> visited(node_cnt + 1, INF);
    pq.push({0, snode});
    visited[snode] = 0;
    while(!pq.empty()) {
        auto[cost, node] = pq.top(); pq.pop();
        if (visited[node] != cost) continue;
        for(int x=0; x<maps[node].size(); x++) {
            int nnode = maps[node][x].first;
            int ncost = cost + maps[node][x].second;
            if (visited[nnode] <= ncost) continue;
            pq.push({ncost, nnode});
            visited[nnode] = ncost;
        }
    }
    return visited;
}

int main() {
    cin>>node_cnt>>edge_cnt>>party_pos;
    maps.resize(node_cnt + 1);
    costs.resize(node_cnt + 1, vector<int>(node_cnt + 1, INF));
    for(int i=0; i<edge_cnt; i++) {
        int node1, node2, cost; cin>>node1>>node2>>cost;
        maps[node1].push_back({node2, cost});
    }

    for(int node = 1; node <= node_cnt; node++) {
        costs[node] = dijkstra(node);
    }

    int answer = -1;
    for(int node = 1; node <= node_cnt; node++) {
        if (costs[node][party_pos] == INF || costs[party_pos][node] == INF) continue;
        answer = max(answer, costs[node][party_pos] + costs[party_pos][node]);
    }
    cout<<answer;
}