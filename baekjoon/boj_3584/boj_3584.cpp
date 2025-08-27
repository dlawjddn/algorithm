#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int node_cnt;
vector<int> parents;

int lca(int node1, int node2) {
    vector<bool> seen(node_cnt + 1, false);
    for(int node = node1; node != 0; node = parents[node]) seen[node] = true;

    for(int node = node2; node != 0; node = parents[node]) {
        if (seen[node]) {
            return node;
        }
    }
    return 0;
}

int main() {
    int test_case; cin>>test_case;
    for(int t=0; t<test_case; t++) {
        cin>>node_cnt;
        parents = vector<int>(node_cnt + 1, 0);
        for(int i=0; i<node_cnt-1; i++) {
            int node1, node2; cin>>node1>>node2;
            parents[node2] = node1;
        }
        int node1, node2; cin>>node1>>node2;
        cout<<lca(node1, node2)<<'\n';
    }
}