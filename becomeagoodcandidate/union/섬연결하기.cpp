#include <string>
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
priority_queue<Info> pq;
vector<int> parents;

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

bool is_valid(int node1, int node2) {
    return find_parent(node1) != find_parent(node2);
}

int solution(int n, vector<vector<int>> costs) {
    int answer = 0;
    for(int i=0; i<n; i++) parents.push_back(i);
    for(int i=0; i<costs.size(); i++) {
        int node1 = costs[i][0];
        int node2 = costs[i][1];
        int cost = costs[i][2];
        pq.push({node1, node2, cost});
    }
    
    for(int i=0; i<n-1; i++) {
        auto[node1, node2, cost] = pq.top(); pq.pop();
        if (is_valid(node1, node2)) {
            make_union(node1, node2);
            answer += cost;
            continue;
        }
        i--;
    }
    return answer;
}