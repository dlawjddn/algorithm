#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct Info {
    int node1, node2, cost;
    bool operator<(Info other) const {
        return cost > other.cost;
    }
};
int node_cnt, edge_cnt;
vector<int> parents;

void init() {
    parents = vector<int>(node_cnt);
    for(int i=0; i<parents.size(); i++) parents[i] = i;
}

int find_parent(int node) {
    if (node == parents[node]) return node;
    return parents[node] = find_parent(parents[node]);
}

void make_union(int node1, int node2) {
    int n1p = find_parent(node1);
    int n2p = find_parent(node2);
    if (n1p < n2p) swap(n1p, n2p);
    parents[n2p] = n1p;
}

bool can_union(int node1, int node2) {
    return find_parent(node1) != find_parent(node2);
}

int main() {
    while(1) {
        cin>>node_cnt>>edge_cnt;
        if (node_cnt == 0 && edge_cnt == 0) break;
        priority_queue<Info> pq;
        init();
        int total_cost = 0;
        for(int i=0; i<edge_cnt; i++) {
            int node1, node2, cost; cin>>node1>>node2>>cost;
            pq.push({node1, node2, cost});
            total_cost += cost;
        }
        int cnt = 0, answer = 0;
        while(!pq.empty()) {
            auto[node1, node2, cost] = pq.top(); pq.pop();
            if (!can_union(node1, node2)) continue;
            make_union(node1, node2);
            answer += cost;
        }
        cout<<total_cost - answer<<"\n";
    }
}