/**
 * @file boj_16562.cpp
 * @brief 백준 gold4 친구비
 * @version 0.1
 * @date 2024-08-01
 * 
 * @copyright Copyright (c) 2024
 * 
 * 부모를 지정하는 방법에 대해 착각했던 부분이 있었다.. 좋다! 하나 알아간다!
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int node_cnt, edge_cnt, budget, answer = 0;
vector<int> costs;
vector<int> parents;
vector<int> checked;

int find_parent(int node) {
    if (node == parents[node]) return node;
    return parents[node] = find_parent(parents[node]);
}

void make_union(int parent, int child) {
    parent = find_parent(parent);
    child = find_parent(child);
    if (costs[parent] >= costs[child]) parents[parent] = child;
    else parents[child] = parent;
}

bool is_same_parent(int node1, int node2) {
    int n1p = find_parent(node1);
    int n2p = find_parent(node2);
    if (n1p == n2p) return true;
    return false;
}

int main(){
    cin>>node_cnt>>edge_cnt>>budget;
    costs.resize(node_cnt + 1);
    parents.resize(node_cnt + 1);
    checked.resize(node_cnt + 1, false);
    for(int i=1; i<=node_cnt; i++) {
        cin>>costs[i];
        parents[i] = i;
    }
    for(int i=0; i<edge_cnt; i++) {
        int node1, node2; cin>>node1>>node2;
        if (is_same_parent(node1, node2)) continue;
        make_union(node1, node2);
    }
    for(int i=1; i<=node_cnt; i++) {
        int parent = find_parent(i);
        if (checked[parent]) continue;
        answer += costs[parent];
        checked[parent] = true;
    }
    cout<<((answer <= budget) ? to_string(answer) : "Oh no");
}