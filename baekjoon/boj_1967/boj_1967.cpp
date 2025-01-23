#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

#define INF 987654321

using namespace std;

int node_cnt;
vector<vector<pair<int, int> > > maps;
vector<int> visited;

bool compare(pair<int, int> p1, pair<int, int> p2) {
    return p1.second > p2.second;
}

int dijkstra(int start) {
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
    visited = vector<int>(node_cnt + 1, INF);
    pq.push({0, start});
    visited[start] = 0;
    while(!pq.empty()) {
        auto[cost, node] = pq.top(); pq.pop();
        if (visited[node] < cost) continue;
        for(int x=0; x<maps[node].size(); x++) {
            int nnode = maps[node][x].first;
            int ncost = cost + maps[node][x].second;
            if (visited[nnode] <= ncost) continue;
            pq.push({ncost, nnode});
            visited[nnode] = ncost;
        }
    }
    int node, node_value = -1;
    for(int i=1; i<=node_cnt; i++) {
        if (node_value < visited[i]) {
            node_value = visited[i];
            node = i;
        }
    }
    return node;
}

int main() {
    cin>>node_cnt;
    maps.resize(node_cnt + 1);
    for(int i=0; i<node_cnt-1; i++) {
        int node1, node2, cost; cin>>node1>>node2>>cost;
        maps[node1].push_back({node2, cost});
        maps[node2].push_back({node1, cost});
    }
    int start = dijkstra(1); // 루트 노드에서 거리가 제일 먼 노드 결정하기
    int end = dijkstra(start);
    cout<<visited[end];
}