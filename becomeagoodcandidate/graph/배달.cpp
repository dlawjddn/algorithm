#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

#define INF 987654321

using namespace std;

vector<vector<pair<int, int> > > maps;
vector<int> visited;

void init(int n) {
    maps.resize(n + 1);
    visited.resize(n + 1, INF);
}

void dijkstra() {
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
    pq.push({0, 1});
    visited[1] = 0;
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
}

int solution(int N, vector<vector<int> > road, int K) {
    int answer = 0;
    init(N);
    for(auto r : road) {
        int node1 = r[0];
        int node2 = r[1];
        int cost = r[2];
        maps[node1].push_back({node2, cost});
        maps[node2].push_back({node1, cost});
    }
    dijkstra();
    for(int i=1; i<=N; i++) {
        if (visited[i] <= K) answer++;
    }
    return answer;
}