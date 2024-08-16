/**
 * @file 가장먼노드_49189.cpp
 * @brief 프로그래머스 lv.3 가장 먼 노드
 * @version 0.1
 * @date 2024-08-16
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <iostream>

#define INF 987654321

using namespace std;

vector<vector<int> > maps;
vector<int> visited;

void print_visited() {
    for(int i=1; i<visited.size(); i++) {
        cout<<visited[i]<<" ";
    }
    cout<<"\n";
}

void dijkstra() {
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
    pq.push({0, 1});
    visited[1] = 0;
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
    //print_visited();
}

int solution(int n, vector<vector<int>> edges) {
    int answer = 0;
    maps.resize(n+1);
    visited.resize(n+1, INF);
    for(auto edge : edges) {
        int node1 = edge[0];
        int node2 = edge[1];
        maps[node1].push_back(node2);
        maps[node2].push_back(node1);
    }
    dijkstra();
    int max_len = 0;
    for(int i=1; i<visited.size(); i++) {
        if (visited[i] == INF) continue;
        if (max_len == visited[i]) answer++;
        else if (max_len < visited[i]) {
            max_len = visited[i];
            answer = 1;
        }
    }
    return answer;
}