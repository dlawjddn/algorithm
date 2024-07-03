/**
 * @file boj_1647.cpp
 * @brief 백준 gold4 도시 분할 계획
 * @version 0.1
 * @date 2024-07-03
 * 
 * @copyright Copyright (c) 2024
 * 
 * MST는 이제 쉽다..
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct Road{
    int src, dest, cost;
    bool operator<(Road other) const {
        return cost > other.cost;
    }
};
int node_cnt = 0, line_cnt = 0, answer = 0;
vector<int> parents;
priority_queue<Road> pq;

Road make_road(int src, int dest, int cost) {
    Road road;
    road.src = src;
    road.dest = dest;
    road.cost = cost;
    return road;
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

int main(){
    cin>>node_cnt>>line_cnt;
    parents.resize(node_cnt + 1);
    for(int i=1; i<parents.size(); i++) parents[i] = i;
    for(int i=0; i<line_cnt; i++) {
        int src, dest, cost; cin>>src>>dest>>cost;
        if (src > dest) {
            pq.push(make_road(dest, src, cost));
        }
        else {
            pq.push(make_road(src, dest, cost));
        }

    }
    int cnt = 0;
    while(cnt < node_cnt - 2) {
        auto[src, dest, cost] = pq.top(); pq.pop();
        if (is_same_parent(src, dest)) continue;
        make_union(src, dest);
        answer += cost;
        cnt++;
    }
    cout<<answer;
}