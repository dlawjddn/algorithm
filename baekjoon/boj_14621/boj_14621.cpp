#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct Info {
    int cost, node1, node2;
    bool operator<(Info other) const {
        return cost > other.cost;
    }
};
int node_cnt, edge_cnt;
vector<bool> men;
vector<int> parents;
priority_queue<Info> pq;

int find_parent(int node) {
    if (node == parents[node]) return node;
    return parents[node] = find_parent(parents[node]);
}

void make_union(int node1, int node2) {
    int n1p = find_parent(node1);
    int n2p = find_parent(node2);
    if (n1p > n2p) swap(n1p, n2p);
    parents[n2p] = n1p;
}

int main() {
    cin>>node_cnt>>edge_cnt;
    men.resize(node_cnt + 1, false);
    parents.resize(node_cnt + 1, 0);
    for(int i=1; i<=node_cnt; i++) parents[i] = i;
    for(int i=1; i<=node_cnt; i++) {
        char sex; cin>>sex;
        if (sex == 'M') men[i] = true;
    }
    for(int i=0; i<edge_cnt; i++) {
        int node1, node2, cost; cin>>node1>>node2>>cost;
        pq.push({cost, node1, node2});
    }
    int cnt = 0, total_cost = 0;
    while(!pq.empty()) {
        auto[cost, node1, node2] = pq.top(); pq.pop();
        if (men[node1] == men[node2]) continue;
        if (find_parent(node1) == find_parent(node2)) continue;
        make_union(node1, node2);
        cnt++;
        total_cost += cost;
    }

    cout<<((cnt == node_cnt - 1) ? total_cost : -1);
}