/**
 * @file boj_17396.cpp
 * @brief 백준 gold5 백도어
 * @version 0.1
 * @date 2024-07-11
 * 
 * @copyright Copyright (c) 2024
 * 
 * 자료형..
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

#define INF 99999999999

using namespace std;

int node_cnt, edge_cnt;
vector<int> exposure;
vector<long long> visited;
vector<vector<pair<int, int> > > maps;


void print_exposure() {
    for(auto value : exposure) cout<<value<<" ";
    cout<<"\n";
}

void print_maps(){
    for(int y=0; y<maps.size(); y++) {
        cout<<"node"<<y<<": ";
        for(int x=0; x<maps[y].size(); x++) {
            cout<<"("<<maps[y][x].first<<", "<<maps[y][x].second<<"), ";
        }
        cout<<"\n";
    }
}

long long dijkstra() {
    priority_queue<pair<long long, int>, vector<pair<long long, int> >, greater<pair<long long, int> > > pq;
    pq.push(make_pair(0, 0));
    visited[0] = 0;
    while(!pq.empty()) {
        auto[cost, pos] = pq.top(); pq.pop();
        if (visited[pos] != cost) continue;
        for(int x=0; x<maps[pos].size(); x++) {
            int npos = maps[pos][x].first;
            long long ncost = cost + (long long) maps[pos][x].second;
            if (visited[npos] <= ncost) continue;
            pq.push(make_pair(ncost, npos));
            visited[npos] = ncost;
        }
    }
    if (visited[node_cnt - 1] == INF) return -1;
    return visited[node_cnt - 1];
}

int main(){
    cin>>node_cnt>>edge_cnt;
    maps.resize(node_cnt);
    exposure.resize(node_cnt);
    visited.resize(node_cnt, INF);
    for(int i=0; i<node_cnt; i++) cin>>exposure[i];
    exposure[node_cnt - 1] = false;
    for(int i=0; i<edge_cnt; i++) {
        int node1, node2, cost; cin>>node1>>node2>>cost;
        if (exposure[node1] || exposure[node2]) continue;
        maps[node1].push_back(make_pair(node2, cost));
        maps[node2].push_back(make_pair(node1, cost));
    }
    cout<<dijkstra();
}