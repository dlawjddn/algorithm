/**
 * @file boj_16202.cpp
 * @brief 백준 gold3 MST 게임
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

struct Info {
    int src, dest, cost;
};
int node_cnt, edge_cnt, turn;
vector<int> result;
vector<int> parents;
vector<vector<int> > maps;
vector<Info> infos;
queue<Info> q;

void print_result(){
    for(auto v : result) cout<<v<<" ";
    cout<<"\n";
}

Info make_info(int src, int dest, int cost) {
    Info info;
    info.src = src;
    info.dest = dest;
    info.cost = cost;
    return info;
}

int find_parent(int node) {
    if (node == parents[node]) return node;
    return parents[node] = find_parent(parents[node]);
}

void make_union(int parent, int child) {
    parent = find_parent(parent);
    child = find_parent(child);
    parents[child] = parent;
}

bool is_same_parent(int node1, int node2) {
    int n1p = find_parent(node1);
    int n2p = find_parent(node2);
    if (n1p == n2p) return true;
    return false;
}

void init_parents() {
    for(int i=1; i<parents.size(); i++) parents[i] = i;
}

int kruskal() {
    int total_cost = 0, total_cnt = 0;
    while(!q.empty()) {
        auto[src, dest, cost] = q.front(); q.pop();
        if (is_same_parent(src, dest)) continue;
        make_union(src, dest);
        total_cost += cost;
        total_cnt++;
    }
    if (total_cnt == node_cnt - 1) return total_cost;
    return 0;
}

int main(){
    cin>>node_cnt>>edge_cnt>>turn;
    result.resize(turn, 0);
    parents.resize(node_cnt + 1);
    maps.resize(node_cnt +1, vector<int>(node_cnt + 1));
    for(int cost = 1; cost <= edge_cnt; cost++) {
        int src, dest; cin>>src>>dest;
        if (src < dest) infos.push_back(make_info(src, dest, cost));
        else infos.push_back(make_info(dest, src, cost));
    }
    for(int i=0; i<turn; i++) {
        init_parents();
        for(int j=i; j<infos.size(); j++) {
            q.push(infos[j]);
        }
        result[i] = kruskal();
        if (result[i] == 0) break;
    }
    print_result();
}