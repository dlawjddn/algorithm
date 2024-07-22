/**
 * @file boj_18352.cpp
 * @author your name (you@domain.com)
 * @brief 백준 silver2 특정 거리의 도시 찾기
 * @version 0.1
 * @date 2024-07-22
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

#define INF 987654321

using namespace std;

int node_cnt, edge_cnt, goal_dist, start;
vector<vector<int> > maps;
vector<int> visited;
vector<int> answer;

void dijkstra() {
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
    pq.push(make_pair(0, start));
    visited[start] = 0;
    while(!pq.empty()) {
        auto[cost, pos] = pq.top(); pq.pop();
        if (visited[pos] != cost) continue;
        for(int x=0; x<maps[pos].size(); x++) {
            int npos = maps[pos][x];
            int ncost = cost + 1;
            if (visited[npos] <= ncost) continue;
            pq.push(make_pair(ncost, npos));
            visited[npos] = ncost;
        }
    }
}

int main(){
    cin>>node_cnt>>edge_cnt>>goal_dist>>start;
    maps.resize(node_cnt + 1);
    visited.resize(node_cnt + 1, INF);
    for(int i=0; i<edge_cnt; i++) {
        int s, e; cin>>s>>e;
        maps[s].push_back(e);
    }
    dijkstra();
    for(int i=1; i<=node_cnt; i++) {
        if (visited[i] == goal_dist) answer.push_back(i);
    }
    if (answer.size() == 0) cout<<"-1";
    else {
        for(auto node : answer) cout<<node<<"\n";
    }
}