#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct Worst {
    int node1, node2, cost;
    bool operator<(Worst other) const {
        return cost > other.cost;
    }
};
struct Best {
    int node1, node2, cost;
    bool operator<(Best other) const {
        return cost < other.cost;
    }
};
int node_cnt, edge_cnt, worst_value = 0, best_value = 0;;
vector<int> parents;
priority_queue<Worst> pq_w;
priority_queue<Best> pq_b;

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

bool cant_union(int node1, int node2) {
    return find_parent(node1) == find_parent(node2);
}

void init_parents() {
    parents = vector<int>(node_cnt + 1, 0);
    for(int i=1; i<=node_cnt; i++) parents[i] = i;
}

int main() {
    cin>>node_cnt>>edge_cnt;
    for(int i=0; i<edge_cnt + 1; i++) {
        int node1, node2, cost; cin>>node1>>node2>>cost;
        pq_w.push({node1, node2, cost});
        pq_b.push({node1, node2, cost});
    }

    // 최악의 경우
    init_parents();
    while(!pq_w.empty()) {
        auto[node1, node2, cost] = pq_w.top(); pq_w.pop();
        if (cant_union(node1, node2)) continue;
        make_union(node1, node2);
        worst_value += cost;
    }

    // 최선의 경우
    init_parents();
    while(!pq_b.empty()) {
        auto[node1, node2, cost] = pq_b.top(); pq_b.pop();
        if (cant_union(node1, node2)) continue;
        make_union(node1, node2);
        best_value += cost;
    }

    cout<<abs((worst_value * worst_value) - (best_value * best_value));
}