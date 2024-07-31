/**
 * @file boj_1005.cpp
 * @brief 백준 gold3 ACM Craft
 * @version 0.1
 * @date 2024-07-31
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int node_cnt, edge_cnt, dest;
vector<vector<int> > maps;
vector<int> parents;
vector<int> build;
vector<int> costs;

void print_costs() {
    cout<<"answer\n";
    for(int i=1; i<=node_cnt; i++) cout<<costs[i]<<" ";
    cout<<"\n";
}

void topology_sort() {
    queue<int> q;
    for(int i=1; i<=node_cnt; i++) {
        if (parents[i] == 0) {
            q.push(i);
            costs[i] = build[i];
        }
    }
    while(!q.empty()) {
        int pos = q.front(); q.pop();
        for(int x=0; x<maps[pos].size(); x++) {
            int npos = maps[pos][x];
            costs[npos] = max(costs[npos], costs[pos] + build[npos]);
            if (--parents[npos] == 0) q.push(npos);
        }
    }
}


int main(){
    int test_case; cin>>test_case;
    for(int t=0; t<test_case; t++) {
        cin>>node_cnt>>edge_cnt;
        maps = vector<vector<int> >(node_cnt + 1);
        parents = vector<int>(node_cnt + 1, 0);
        build = vector<int>(node_cnt + 1, 0);
        costs = vector<int>(node_cnt + 1, 0);
        for(int i=1; i<=node_cnt; i++) cin>>build[i];
        for(int i=1; i<=edge_cnt; i++) {
            int node1, node2; cin>>node1>>node2;
            maps[node1].push_back(node2);
            parents[node2] += 1;
        }
        cin>>dest;
        topology_sort();
        cout<<costs[dest]<<"\n";
    }
}