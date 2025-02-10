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
int node_cnt, total_cost = 0;
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

bool cant_union(int node1, int node2) {
    return find_parent(node1) == find_parent(node2);
}

int main() {
    cin>>node_cnt;
    parents.resize(node_cnt, 0);
    for(int i=0; i<node_cnt; i++) parents[i] = i;

    for(int y=0; y<node_cnt; y++) {
        string str; cin>>str;
        for(int x=0; x<node_cnt; x++) {
            int cost;
            if ('a' <= str[x] && str[x] <= 'z') cost = str[x] - 'a' + 1;
            else if ('A' <= str[x] && str[x] <= 'Z') cost = str[x] - 'A' + 27;
            else continue;
            pq.push({y, x, cost});
            total_cost += cost;
        }
    }

    int need_value = 0, need_cnt = 0;
    while(!pq.empty()) {
        auto[node1, node2, cost] = pq.top(); pq.pop();
        if (cant_union(node1, node2)) continue;
        make_union(node1, node2);
        need_cnt++;
        need_value += cost;
    }

    cout<<((need_cnt != node_cnt - 1) ? -1 : total_cost - need_value);
}