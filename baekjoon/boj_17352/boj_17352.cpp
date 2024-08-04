/**
 * @file boj_17352.cpp
 * @brief 백준 gold5 여러분의 다리가 되어 드리겠습니다!
 * @version 0.1
 * @date 2024-08-04
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int node_cnt;
vector<int> parents;

int find_parent(int node) {
    if (node == parents[node]) return node;
    return parents[node] = find_parent(parents[node]);
}

void make_union(int parent, int child) {
    parent = find_parent(parent);
    child = find_parent(child);
    if (parent < child) parents[child] = parent;
    else parents[parent] = child;
}

bool is_same_parent(int node1, int node2) {
    return find_parent(node1) == find_parent(node2);
}

int main(){
    cin>>node_cnt;
    parents.resize(node_cnt + 1);
    for(int i=1; i<=node_cnt; i++) parents[i] = i;
    for(int i=0; i<node_cnt - 2; i++) {
        int node1, node2; cin>>node1>>node2;
        make_union(node1, node2);
    }
    for(int i=1; i<=node_cnt; i++) {
        for(int j=1; j<=node_cnt; j++) {
            if (i == j) continue;
            if (!is_same_parent(i, j)) {
                cout<<i<<" "<<j;
                return 0;
            }
        }
    }
}