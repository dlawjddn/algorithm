#include <iostream>
#include <vector>

using namespace std;

int node_cnt, deleted, root, answer = 0;
vector<vector<int>> maps;
vector<bool> visited;

int dfs(int node) {
    if (maps[node].empty()) return 1; // 자식이 없는 경우 리프 노드

    int leaf_count = 0;
    for (int x = 0; x < maps[node].size(); x++) {
        int nnode = maps[node][x];
        if (visited[nnode] || nnode == deleted) continue;
        visited[nnode] = true;
        leaf_count += dfs(nnode);
    }
    if (maps[node].size() == 1 && maps[node].front() == deleted) leaf_count++;

    return leaf_count;
}

int main() {
    cin >> node_cnt;
    maps.resize(node_cnt);
    visited.resize(node_cnt, false);

    for (int i = 0; i < node_cnt; i++) {
        int parent; cin >> parent;
        if (parent == -1) root = i;
        else maps[parent].push_back(i);
    }
    cin >> deleted;

    if (deleted == root) {
        cout << 0;
        return 0;
    }
    cout << dfs(root);
}
