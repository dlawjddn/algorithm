#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int node_cnt, edge_cnt, spos, dpos;
vector<vector<pair<int, int> > > maps;
vector<int> visited;

int dijkstra() {
    priority_queue<pair<int, int>, vector<pair<int, int> >, less<pair<int, int> > > pq;
    visited[spos] = 1000000;
    for(int x=0; x<maps[spos].size(); x++) {
        auto[node, value] = maps[spos][x];
        pq.push({value, node});
        visited[node] = value;
    }
    while(!pq.empty()) {
        auto[value, node] = pq.top(); pq.pop();
        if (visited[node] != value) continue;
        for(int x=0; x<maps[node].size(); x++) {
            int nnode = maps[node][x].first;
            int nvalue = min(value, maps[node][x].second);
            if (nvalue <= visited[nnode]) continue;
            pq.push({nvalue, nnode});
            visited[nnode] = nvalue;
        }
    }
    return visited[dpos];
}

int main() {
    cin>>node_cnt>>edge_cnt>>spos>>dpos;
    maps.resize(node_cnt + 1);
    visited.resize(node_cnt + 1, 0);
    for(int i=0; i<edge_cnt; i++) {
        int node1, node2, cost; cin>>node1>>node2>>cost;
        maps[node1].push_back({node2, cost});
        maps[node2].push_back({node1, cost});
    }
    cout<<dijkstra();
}