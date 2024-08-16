/**
 * @file 섬연결하기_42861.cpp
 * @brief 프로그래머스 lv.3 섬 연결하기
 * @version 0.1
 * @date 2024-08-17
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <string>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

vector<int> parents;
priority_queue<pair<int, pair<int, int> >, vector<pair<int, pair<int, int> > >, greater<pair<int, pair<int, int> > > > pq;

int find_parent(int node) {
    if (node == parents[node]) return node;
    return parents[node] = find_parent(parents[node]);
}

void make_union(int parent, int child) {
    parent = find_parent(parent);
    child = find_parent(child);
    if (parent > child) swap(parent, child);
    parents[child] = parent;
}

bool is_same_parent(int node1, int node2) {
    return find_parent(node1) == find_parent(node2);
}

int solution(int n, vector<vector<int>> costs) {
    int answer = 0;
    parents.resize(n+1, 0);
    for(int i=1; i<=n; i++) parents[i] = i;
    for(auto cost_info : costs) {
        int node1 = cost_info[0];
        int node2 = cost_info[1];
        int cost = cost_info[2];
        pq.push({cost, {node1, node2}});
    }
    for(int i=0; i<n-1; i++) {
        auto[cost, nodes] = pq.top(); pq.pop();
        auto[node1, node2] = nodes;
        if (is_same_parent(node1, node2)) {
            i--;
            continue;
        }
        answer += cost;
        make_union(node1, node2);
    }
    return answer;
}