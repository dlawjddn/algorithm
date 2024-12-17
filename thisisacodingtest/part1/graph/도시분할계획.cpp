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
int node_cnt, edge_cnt, answer = 0, last = 0;
vector<int> parents;
vector<vector<pair<int, int> > > maps;
priority_queue<Info> pq;

void init() {
    maps.resize(node_cnt + 1);
    parents.resize(node_cnt+1);
    for(int i=1; i<=node_cnt; i++) parents[i] = i;
}

int find_parent(int node) {
    if (node == parents[node]) return node;
    return parents[node] = find_parent(parents[node]);
}

void make_union(int node1, int node2) {
    int n1p = find_parent(node1);
    int n2p = find_parent(node2);
    if (n1p < n2p) parents[n2p] = n1p;
    else parents[n1p] = n2p;
}

int main() {
    cin>>node_cnt>>edge_cnt;
    init();
    for(int i=0; i<edge_cnt; i++) {
        int node1, node2, cost; cin>>node1>>node2>>cost;
        pq.push({node1, node2, cost});
    }
    while(!pq.empty()) {
        auto[node1, node2, cost] = pq.top(); pq.pop();
        if (find_parent(node1) == find_parent(node2)) continue;
        make_union(node1, node2);
        answer += cost;
        last = cost;
    }
    cout<<answer - last;
}