/**
 * @file boj_2307.cpp
 * @brief 백준 gold1 도로검문
 * @version 0.1
 * @date 2024-08-01
 * 
 * @copyright Copyright (c) 2024
 * 
 * 다익스트라 이제 그만 풀까.. 너무 잘하는데..
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

#define INF 987654321

using namespace std;

int node_cnt, edge_cnt, answer = 0;
vector<int> parents;
vector<pair<int, int> > edges;
vector<vector<pair<int, int> > > maps;
vector<int> shortest_visited;

void print_shortest_visited() {
    for(int i=1; i<=node_cnt; i++) cout<<shortest_visited[i]<<" ";
    cout<<"\n";
}

void print_edges() {
    for(auto edge : edges) cout<<edge.first<<" "<<edge.second<<"\n";
}

void dijkstra() {
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
    pq.push({0, 1});
    shortest_visited[1] = 0;
    while(!pq.empty()) {
        auto[cost, pos] = pq.top(); pq.pop();
        if (shortest_visited[pos] != cost) continue;
        for(int x=0; x<maps[pos].size(); x++) {
            int npos = maps[pos][x].first;
            int ncost = cost + maps[pos][x].second;
            if (shortest_visited[npos] <= ncost) continue;
            pq.push({ncost, npos});
            shortest_visited[npos] = ncost;
            parents[npos] = pos;
        }
    }
}

void find_shortest_path() {
    int pos = node_cnt;
    while(parents[pos] != 0) {
        int bpos = parents[pos];
        edges.push_back({bpos, pos});
        pos = bpos;
    }
}

int after_delete(int node1, int node2) {
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
    vector<int> visited(node_cnt + 1, INF);
    pq.push({0, 1});
    visited[1] = 0;
    while(!pq.empty()) {
        auto[cost, pos] = pq.top(); pq.pop();
        if (visited[pos] != cost) continue;
        for(int x=0; x<maps[pos].size(); x++) {
            int npos = maps[pos][x].first;
            int ncost = cost + maps[pos][x].second;
            if ((pos == node1 && npos == node2) || (pos == node2 && npos == node1)) continue;
            if (visited[npos] <= ncost) continue;
            pq.push({ncost, npos});
            visited[npos] = ncost;
        }
    }
    return (visited[node_cnt] == INF) ? INF : visited[node_cnt] - shortest_visited[node_cnt]; 
}

int main(){
    cin>>node_cnt>>edge_cnt;
    maps.resize(node_cnt + 1);
    shortest_visited.resize(node_cnt + 1, INF);
    parents.resize(node_cnt + 1, 0);
    for(int i=0; i<edge_cnt; i++) {
        int node1, node2, cost; cin>>node1>>node2>>cost;
        maps[node1].push_back({node2, cost});
        maps[node2].push_back({node1, cost});
    }
    dijkstra();
    find_shortest_path();
    //print_edges();
    for(auto edge : edges) {
        answer = max(answer, after_delete(edge.first, edge.second));
        if (answer == INF) {
            cout<<"-1";
            return 0;
        }
    }
    cout<<answer;
}