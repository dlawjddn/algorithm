/**
 * @file boj_20040.cpp
 * @brief 백준 gold4 사이클 게임
 * @version 0.1
 * @date 2024-07-28
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int node_cnt, edge_cnt, answer = 0;
vector<int> parents;

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

int main(){
    cin>>node_cnt>>edge_cnt;
    parents.resize(node_cnt);
    for(int i=0; i<node_cnt; i++) parents[i] = i;
    for(int i=0; i<edge_cnt; i++) {
        int node1, node2; cin>>node1>>node2;
        if (node1 > node2) swap(node1, node2);
        if (is_same_parent(node1, node2)) {
            answer = i+1;
            break;
        }
        make_union(node1, node2);
    }
    cout<<answer;
}