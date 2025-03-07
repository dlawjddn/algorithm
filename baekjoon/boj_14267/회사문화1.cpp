#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int node_cnt, actions_cnt;
vector<vector<int> > maps;
vector<bool> visited;
vector<int> answer;

void dfs(int node, int value) {
    visited[node] = true;
    answer[node] += value;
    for(int x=0; x<maps[node].size(); x++) {
        int nnode = maps[node][x];
        if (visited[nnode]) continue;
        dfs(nnode, answer[node]);
    }
}

int main() {
    cin>>node_cnt>>actions_cnt;
    answer.resize(node_cnt + 1, 0);
    visited.resize(node_cnt + 1, false);
    maps.resize(node_cnt + 1);
    for(int i=1; i<=node_cnt; i++) {
        int parent; cin>>parent;
        if (parent == -1) continue;
        maps[parent].push_back(i);
    }
    for(int i=0; i<actions_cnt; i++) {
        int node, value; cin>>node>>value;
        answer[node] += value;
    }
    dfs(1, 0);

    for(int i=1; i<=node_cnt; i++) cout<<answer[i]<<" ";
}