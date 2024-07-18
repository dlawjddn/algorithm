/**
 * @file boj_16681.cpp
 * @brief 백준 gold2 등산
 * @version 0.1
 * @date 2024-07-18
 * 
 * @copyright Copyright (c) 2024
 * 
 * long long의 최대값은 1e18!!
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <string>

#define INF 1e18

using namespace std;

int node_cnt, edge_cnt, health_cost, happy;
vector<int> heights;
vector<long long> up_cost;
vector<long long> down_cost;
vector<vector<pair<int, int> > > maps;

void print_cost() {
    cout<<"up_cost\n";
    for(int i=1; i<=node_cnt; i++) cout<<up_cost[i]<<" ";
    cout<<"\n";
    cout<<"down_cost\n";
    for(int i=1; i<=node_cnt; i++) cout<<down_cost[i]<<" ";
    cout<<"\n";
}

vector<long long> dijsktra(int spos){
    priority_queue<pair<long long, int>, vector<pair<long long, int> >, greater<pair<long long, int> > > pq;
    vector<long long> visited(node_cnt + 1, INF);
    pq.push(make_pair(0, spos));
    visited[spos] = 0;
    while(!pq.empty()){
        auto[cost, pos] = pq.top(); pq.pop();
        if (visited[pos] != cost) continue;
        for(int x=0; x<maps[pos].size(); x++) {
            int npos = maps[pos][x].first;
            long long ncost = cost + maps[pos][x].second;
            if (visited[npos] <= ncost || heights[pos] >= heights[npos]) continue;
            pq.push(make_pair(ncost, npos));
            visited[npos] = ncost;
        }
    }
    return visited;
}

int main(){
    cin>>node_cnt>>edge_cnt>>health_cost>>happy;
    maps.resize(node_cnt + 1);
    heights.resize(node_cnt + 1);
    for(int i=1; i<=node_cnt; i++) cin>>heights[i];
    for(int i=0; i<edge_cnt; i++) {
        int node1, node2, dist; cin>>node1>>node2>>dist;
        maps[node1].push_back(make_pair(node2, dist * health_cost));
        maps[node2].push_back(make_pair(node1, dist * health_cost));
    }
    up_cost = dijsktra(1);
    down_cost = dijsktra(node_cnt);
    long long answer = -1 * INF;
    for(int i=1; i<=node_cnt; i++) {
        if (up_cost[i] == INF || down_cost[i] == INF) continue;
        long long total_happy = heights[i] * happy;
        answer = max(answer, total_happy - (up_cost[i] + down_cost[i]));
    }
    cout<<((answer == -1 * INF) ? "Impossible" : to_string(answer));
}