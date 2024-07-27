/**
 * @file boj_1717.cpp
 * @brief 백준 gold5 집합의 표현
 * @version 0.1
 * @date 2024-07-27
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <vector>

using namespace std;

int node_cnt, edge_cnt;
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
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>node_cnt>>edge_cnt;
    parents.resize(node_cnt + 1);
    for(int i=1; i<=node_cnt; i++) parents[i] = i;
    for(int i=0; i<edge_cnt; i++) {
        int order, node1, node2; cin>>order>>node1>>node2;
        if (node1 > node2) swap(node1, node2);
        if (order == 0) make_union(node1, node2);
        else cout<<(is_same_parent(node1, node2) ? "YES\n": "NO\n");
    }

}