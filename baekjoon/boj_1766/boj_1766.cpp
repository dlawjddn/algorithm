/**
 * @file boj_1766.cpp
 * @brief 백준 gold2 문제집
 * @version 0.1
 * @date 2024-07-11
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int vertex_cnt, edge_cnt;
vector<int> result;
vector<int> in_degree;
vector<vector<int> > maps;

void topology_sort() {
    priority_queue<int, vector<int>, greater<int> > pq;
    for(int i=1; i<in_degree.size(); i++) {
        if (in_degree[i] == 0) pq.push(i);
    }
    while(!pq.empty()) {
        int node = pq.top(); pq.pop();
        result.push_back(node);
        for(int i=0; i<maps[node].size(); i++) {
            int connected = maps[node][i];
            in_degree[connected] -= 1;
            if (in_degree[connected] == 0) pq.push(connected);
        }
    }
    for(auto r : result) cout<<r<<" ";
}

int main(){
    cin>>vertex_cnt>>edge_cnt;
    in_degree.resize(vertex_cnt + 1, 0);
    maps.resize(vertex_cnt + 1, vector<int>());
    for(int i=0; i<edge_cnt; i++) {
        int src, dest; cin>>src>>dest;
        maps[src].push_back(dest);
        in_degree[dest]++;
    }
    topology_sort();
}