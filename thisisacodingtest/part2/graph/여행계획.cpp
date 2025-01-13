#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

int place_cnt, plan_cnt;
set<int> result;
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

int main() {
    cin>>place_cnt>>plan_cnt;
    parents.resize(place_cnt + 1);
    for(int i=1; i<=place_cnt; i++) parents[i] = i;

    for(int i=1; i<=place_cnt; i++) {
        for(int j=1; j<=place_cnt; j++) {
            bool is_connected; cin>>is_connected;
            if (is_connected) make_union(i, j);
        }
    }

    for(int i=0; i<plan_cnt; i++) {
        int city; cin>>city;
        result.insert(find_parent(city));
    }
    cout<<((result.size() == 1) ? "YES" : "NO");
}