#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

#define INF 987654321

using namespace std;

struct Info {
    int node, cost, type;
    bool operator<(Info other) const {
        return cost > other.cost;
    }
};
int node_cnt, edge_cnt, snode, enode;
vector<vector<pair<int, int> > >maps;

int dijkstra(int type) {
    priority_queue<Info> pq;
    vector<int> visited(node_cnt + 1, INF);
    pq.push({snode, 0, type});
    visited[snode] = 0;
    while(!pq.empty()) {
        auto[node, cost, type] = pq.top(); pq.pop();
        if (visited[node] != cost) continue;
        for(int x=0; x<maps[node].size(); x++) {
            int nnode = maps[node][x].first;
            int ntype = maps[node][x].second;
            int ncost = cost + ((type == ntype) ? 0 : 1);
            if (visited[nnode] <= ncost) continue;
            pq.push({nnode, ncost, ntype});
            visited[nnode] = ncost;
        }
    }
    return visited[enode];
}

int main() {
    cin>>node_cnt>>edge_cnt;
    maps.resize(node_cnt + 1);
    for(int i=0; i<edge_cnt; i++) {
        int node1, node2, type; cin>>node1>>node2>>type;
        maps[node1].push_back({node2, type});
        maps[node2].push_back({node1, type});
    }
    cin>>snode>>enode;
    cout<<min(dijkstra(0), dijkstra(1));
}