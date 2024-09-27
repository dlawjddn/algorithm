/**
 * @file 배달_12978.cpp
 * @brief 프로그래머스 lv.2 Summer/Winter Coding(~2018) 배달
 * @version 0.1
 * @date 2024-08-07
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

#define INF 1e15

using namespace std;

vector<vector<pair<int, int> > > maps;
vector<long long> visited;

int dijkstra(int k) {
    priority_queue<pair<long long, int>, vector<pair<long long, int> >, greater<pair<long long, int> > > pq;
    pq.push({0, 1});
    visited[1] = 0;
    while(!pq.empty()) {
        auto[cost, pos] = pq.top(); pq.pop();
        if (visited[pos] != cost) continue;
        for(int x=0; x<maps[pos].size(); x++) {
            int npos = maps[pos][x].first;
            int ncost = cost + maps[pos][x].second;
            if (visited[npos] <= ncost) continue;
            pq.push({ncost, npos});
            visited[npos] = ncost;
        }
    }
    int cnt = 0;
    for(int i=1; i<visited.size(); i++) {
        if (visited[i] <= k) cnt++;
    }
    return cnt;
}

int solution(int N, vector<vector<int> > roads, int K) {
    maps.resize(N+1);
    visited.resize(N+1, INF);
    for(auto road : roads) {
        int node1 = road[0];
        int node2 = road[1];
        int cost = road[2];
        maps[node1].push_back({node2, cost});
        maps[node2].push_back({node1, cost});
    }
    return dijkstra(K);
}
/**
 * @file 배달_12978.cpp
 * @brief 프로그래머스 lv.2 배달
 * @version 0.1
 * @date 2024-09-27
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

#define INF 500001

using namespace std;

vector<vector<pair<int, int> > > maps;
vector<int> visited;

void dijkstra() {
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
    pq.push({0, 1});
    visited[1] = 0;
    while(!pq.empty()) {
        auto[cost, pos] = pq.top(); pq.pop();
        if (visited[pos] != cost) continue;
        for(int x=0; x<maps[pos].size(); x++) {
            int npos = maps[pos][x].first;
            int ncost = cost + maps[pos][x].second;
            if (visited[npos] <= ncost) continue;
            pq.push({ncost, npos});
            visited[npos] = ncost;
        }
    }
}

int solution(int N, vector<vector<int> > road, int K) {
    int answer = 0;
    maps.resize(N + 1);
    visited.resize(N + 1, INF);
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