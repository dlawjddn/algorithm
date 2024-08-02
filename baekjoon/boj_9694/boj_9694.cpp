/**
 * @file boj_9694.cpp
 * @brief 백준 gold3 무엇을 아느냐가 아니라 누구를 아느냐가 문제다
 * @version 0.1
 * @date 2024-08-03
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

int node_cnt, edge_cnt;
vector<vector<pair<int, int> > > maps;
vector<int> visited;
vector<int> parents;

bool dijkstra() {
    priority_queue<pair<int, int>, vector<pair<int, int> > , greater<pair<int, int> > > pq;
    pq.push({0, 0});
    visited[0] = 0;
    while(!pq.empty()) {
        auto[cost, pos] = pq.top(); pq.pop();
        if (visited[pos] != cost) continue;
        for(int x=0; x<maps[pos].size(); x++) {
            int npos = maps[pos][x].first;
            int ncost = cost + maps[pos][x].second;
            if (visited[npos] <= ncost) continue;
            pq.push({ncost, npos});
            visited[npos] = ncost;
            parents[npos] = pos;
        }
    }
    return (visited[node_cnt - 1] == INF ? false : true);
}

int main(){
    int test_case; cin>>test_case;
    for(int t=1; t<=test_case; t++) {
        cin>>edge_cnt>>node_cnt;
        maps = vector<vector<pair<int, int> > >(node_cnt);
        visited = vector<int>(node_cnt, INF);
        parents = vector<int>(node_cnt, -1);
        for(int i=0; i<edge_cnt; i++) {
            int node1, node2, cost; cin>>node1>>node2>>cost;
            maps[node1].push_back({node2, cost});
            maps[node2].push_back({node1, cost});
        }
        cout<<"Case #"<<t<<": ";
        if (dijkstra()) {
            vector<int> result;
            int pos = node_cnt - 1;
            while(pos != -1) {
                result.push_back(pos);
                pos = parents[pos];
            }
            for(int j=result.size()-1; j>=0; j--) cout<<result[j]<<" ";
        }
        else cout<<"-1";
        cout<<"\n";
    }
}