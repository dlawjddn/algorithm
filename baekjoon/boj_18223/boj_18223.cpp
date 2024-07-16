/**
 * @file boj_18223.cpp
 * @brief 백준 gold4 민준이와 마산 그리고 건우
 * @version 0.1
 * @date 2024-07-16
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

int node_cnt, edge_cnt, friend_pos;
vector<vector<pair<int, int> > > maps;
vector<int> visited_from_start;
vector<int> visited_from_friend;

vector<int> dijkstra(int spos) {
    priority_queue<pair<int,int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
    vector<int> visited(node_cnt + 1, INF);
    pq.push(make_pair(0, spos));
    visited[spos] = 0;
    while(!pq.empty()) {
        auto[cost, pos] = pq.top(); pq.pop();
        if (visited[pos] != cost) continue;
        for(int x=0; x<maps[pos].size(); x++) {
            int npos = maps[pos][x].first;
            int ncost = cost + maps[pos][x].second;
            if (visited[npos] <= ncost) continue;
            pq.push(make_pair(ncost, npos));
            visited[npos] = ncost;
        }
    }
    return visited;
}

int main(){
    cin>>node_cnt>>edge_cnt>>friend_pos;
    maps.resize(node_cnt + 1);
    for(int i=0; i<edge_cnt; i++) {
        int node1, node2, cost; cin>>node1>>node2>>cost;
        maps[node1].push_back(make_pair(node2, cost));
        maps[node2].push_back(make_pair(node1, cost));
    }
    visited_from_start = dijkstra(1);
    visited_from_friend = dijkstra(friend_pos);
    cout<<((visited_from_start.back() < visited_from_start[friend_pos] + visited_from_friend.back()) ? "GOOD BYE" : "SAVE HIM");
}