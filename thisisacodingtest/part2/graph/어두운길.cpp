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
int node_cnt, edge_cnt, total_cost = 0, final_cost = 0;
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

bool is_vaild(int node1, int node2) {
    return find_parent(node1) != find_parent(node2);
}

int main() {
    cin>>node_cnt>>edge_cnt;
    parents.resize(node_cnt + 1);
    for(int i=0; i<node_cnt; i++) parents[i] = i;

    for(int i=0; i<edge_cnt; i++) {
        int node1, node2, cost; cin>>node1>>node2>>cost;
        total_cost += cost;
        pq.push({node1, node2, cost});
    }
    int cnt = 0;
    while(!pq.empty() && cnt < node_cnt - 1) {
        auto[node1, node2, cost] = pq.top(); pq.pop();
        if (is_vaild(node1, node2)) {
            make_union(node1, node2);
            final_cost+= cost;
            cnt++;
        }
    }
    cout<<total_cost - final_cost;
}