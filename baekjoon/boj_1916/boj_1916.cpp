#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

#define INF 987654321

using namespace std;

int vertex_cnt, edge_cnt, start, destination;
vector<int> visited;
vector<vector<pair<int, int> > > maps;

int dijkstra() {
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
    pq.push(make_pair(0, start));
    visited[start] = 0;
    while(!pq.empty()) {
        auto[cost, pos] = pq.top(); pq.pop();
        if (visited[pos] != cost) continue;
        for(int x=0; x<maps[pos].size(); x++) {
            int ncost = cost + maps[pos][x].first;
            int npos = maps[pos][x].second;
            if (visited[npos] <= ncost) continue;
            pq.push(make_pair(ncost, npos));
            visited[npos] = ncost;
        }
    }
    return visited[destination];
}

int main() {
    cin>>vertex_cnt>>edge_cnt;
    visited.resize(vertex_cnt + 1, INF);
    maps.resize(vertex_cnt + 1, vector<pair<int, int> >());
    for(int i=0; i<edge_cnt; i++) {
        int src, dest, cost; cin>>src>>dest>>cost;
        maps[src].push_back(make_pair(cost, dest));
    }
    cin>>start>>destination;
    cout<<dijkstra();
}