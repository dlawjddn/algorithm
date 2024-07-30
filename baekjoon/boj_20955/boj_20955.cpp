/**
 * @file boj_20955.cpp
 * @brief 백준 gold4 민서의 응급수술
 * @version 0.1
 * @date 2024-07-30
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

int node_cnt, edge_cnt, answer;
vector<int> parents;
set<int> node_boss;

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
    parents.resize(node_cnt + 1);
    for(int i=1; i<=node_cnt; i++) parents[i] = i;
    for(int i=0; i<edge_cnt; i++) {
        int node1, node2; cin>>node1>>node2;
        if (node1 > node2) swap(node1, node2);
        if (is_same_parent(node1, node2)) answer++; // 사이클을 만드는 간선 제거
        else make_union(node1, node2);
    }
    // 연결된 간선들의 무리를 찾아서 무리마다 연결 추가하기
    for(int i=1; i<=node_cnt; i++) {
        node_boss.insert(find_parent(i));
    }
    answer += node_boss.size() - 1;
    cout<<answer;
}