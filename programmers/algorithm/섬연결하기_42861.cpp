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
/**
 * @file 섬연결하기_42861.cpp
 * @brief 프로그래머스 lv.3 섬 연결하기
 * @version 0.1
 * @date 2024-09-27
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Info {
    int node1, node2, cost;
    bool operator<(Info other) const {
        return cost > other.cost;
    }
};
vector<int> parents;
priority_queue<Info> pq;

Info make_info(int node1, int node2, int cost) {
    Info info;
    info.node1 = node1;
    info.node2 = node2;
    info.cost = cost;
    return info;
}

int find_parent(int node) {
    if(node == parents[node]) return node;
    return find_parent(parents[node]);
}

void make_union(int parent, int child) {
    if (parent > child) swap(parent, child);
    parent = find_parent(parent);
    child = find_parent(child);
    parents[child] = parent;
}

bool is_same_parent(int node1, int node2) {
    int n1p = find_parent(node1);
    int n2p = find_parent(node2);
    return n1p == n2p;
}

int solution(int n, vector<vector<int>> costs) {
    int answer = 0;
    parents.resize(n);
    for(int i=0; i<n; i++) parents[i] = i;
    for(auto c : costs) {
        pq.push(make_info(c[0], c[1], c[2]));
    }
    while(!pq.empty()) {
        auto[node1, node2, cost] = pq.top(); pq.pop();
        if (is_same_parent(node1, node2)) continue;
        make_union(node1, node2);
        answer += cost;
    }
    return answer;
}

