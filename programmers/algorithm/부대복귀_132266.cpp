#include <string>
#include <vector>
#include <iostream>
#include <queue>

using namespace std;

vector<vector<int> > maps(100001);

void make_map(vector<vector<int> > roads){
    for(int y=0; y<roads.size(); y++){
        int start = roads[y][0];
        int end = roads[y][1];
        maps[start].push_back(end);
        maps[end].push_back(start);
    }
}

int bfs(int size, int spos, int dest){
    vector<int> visited(size + 1, 0);
    queue<int> q;
    q.push(spos);
    visited[spos] = 1;
    while(!q.empty()){
        int pos = q.front(); q.pop();
        if (pos == dest){
            return visited[pos] - 1;
        }
        for(int d=0; d<maps[pos].size(); d++){
            int npos = maps[pos][d];
            if (visited[npos] != 0) continue;
            q.push(npos);
            visited[npos] = visited[pos] + 1;
        }
    }
    return -1;
}

vector<int> solve(int n, vector<int> sources, int dest){
    vector<int> answer;
    for(int i=0; i<sources.size(); i++){
        answer.push_back(bfs(n, sources[i], dest));
    }
    return answer;
}

vector<int> solution(int n, vector<vector<int>> roads, vector<int> sources, int destination) {
    make_map(roads);
    return solve(n, sources, destination);
}

/**
 * @file 부대복귀_132266.cpp
 * @brief 프로그래머스 lv.3 부대복귀
 * @version 0.1
 * @date 2024-08-20
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <string>
#include <vector>
#include <algorithm>
#include <queue>

#define INF 987654321

using namespace std;

vector<vector<int> > maps;
vector<int> visited;

void dijkstra(int spos) {
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
    pq.push({0, spos});
    visited[spos] = 0;
    while(!pq.empty()) {
        auto[cost, pos] = pq.top(); pq.pop();
        if (visited[pos] != cost) continue;
        for(int x=0; x<maps[pos].size(); x++) {
            int npos = maps[pos][x];
            int ncost = cost + 1;
            if (visited[npos] <= ncost) continue;
            pq.push({ncost, npos});
            visited[npos] = ncost;
        }
    }
}

vector<int> solution(int n, vector<vector<int>> roads, vector<int> sources, int destination) {
    vector<int> answer;
    maps.resize(n+1);
    visited.resize(n+1, INF);
    for(auto src : roads) {
        maps[src[0]].push_back(src[1]);
        maps[src[1]].push_back(src[0]);
    }
    dijkstra(destination);
    for(auto src : sources) {
        int cost = (visited[src] == INF) ? -1 : visited[src];
        answer.push_back(cost);
    }
    return answer;
}