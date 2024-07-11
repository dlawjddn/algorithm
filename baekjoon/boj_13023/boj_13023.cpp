/**
 * @file boj_13023.cpp
 * @brief 백준 gold5 ABCDE
 * @version 0.1
 * @date 2024-07-11
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool answer = false;
int node_cnt, edge_cnt;
vector<vector<int> > maps;
vector<bool> visited;

bool is_everybody_friends() {
    for (auto v : visited) {
        if (!v) return false;
    }
    return true;
}

void dfs(int pos, int depth) {
    visited[pos] = true;
    if (depth == 5) {
        answer = true;
        return ;
    }
    for(int x=0; x<maps[pos].size(); x++) {
        if (visited[maps[pos][x]]) continue;
        dfs(maps[pos][x], depth + 1);
    }
    visited[pos] = false;
}

int main(){
    cin>>node_cnt>>edge_cnt;
    maps.resize(node_cnt);
    for(int i=0; i<edge_cnt; i++) {
        int node1, node2; cin>>node1>>node2;
        maps[node1].push_back(node2);
        maps[node2].push_back(node1);
    }
    for(int i=0; i<node_cnt; i++) {
        visited = vector<bool>(node_cnt, false);
        dfs(i, 1);
        if (answer) {
            cout<<"1";
            return 0;
        }
    }
    cout<<"0";
}