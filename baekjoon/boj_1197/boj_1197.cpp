/**
 * @file boj_1197.cpp
 * @brief 백준 gold4 최소 스패닝 트리
 * @version 0.1
 * @date 2024-07-02
 * 
 * @copyright Copyright (c) 2024
 * 
 * easy
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct Info {
    int src, dest, cost;

    bool operator<(Info other) const {
        return cost > other.cost;
    }
};
int node_cnt = 0, road_cnt = 0, answer = 0, cnt = 0;
vector<int> parents(100001);
vector<vector<int> > tree(100001);
priority_queue<Info> pq;

Info make_info(int src, int dest, int cost) {
    Info info;
    info.src = src;
    info.dest = dest;
    info.cost = cost;
    return info;
}

int find_parent(int num) {
    if (num == parents[num]) return num;
    return parents[num] = find_parent(parents[num]);
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
    cin>>node_cnt>>road_cnt;
    parents.resize(node_cnt + 1);
    for(int i=0; i<road_cnt; i++) {
        int src, dest, cost; cin>>src>>dest>>cost;
        pq.push(make_info(src, dest, cost));
    }
    // 유니온 파인드 기초 세팅
    for(int i=0; i<parents.size(); i++) parents[i] = i;
    while(!pq.empty()) {
        auto [src, dest, cost] = pq.top(); pq.pop();
        if (is_same_parent(src, dest)) continue;
        make_union(src, dest);
        answer += cost;
        cnt++;
        if (cnt == node_cnt - 1) break;
    }
    cout<<answer;
}