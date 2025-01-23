#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int node_cnt;
bool answer = false;
vector<vector<int> > maps;
vector<bool> visited;
vector<int> path;

void dfs(int pos, int idx) {
    cout<<pos<<" ";
    visited[pos] = true;
    if (path[idx] != pos) return ;
    if (idx == path.size() - 1) {
        answer = true;
        return ;
    }
    for(int x=0; x<maps[pos].size(); x++) {
        if (visited[maps[pos][x]]) continue;
        dfs(maps[pos][x], idx+1);
    }
    visited[pos] = false;
}

int main(){
    cin>>node_cnt;
    maps.resize(node_cnt + 1);
    visited.resize(node_cnt + 1, false);
    path.resize(node_cnt);
    for(int i=0; i<node_cnt-1; i++) {
        int node1, node2; cin>>node1>>node2;
        maps[node1].push_back(node2);
        maps[node2].push_back(node1);
    }
    for(int i=1; i<=node_cnt; i++) {
        cin>>path[i-1];
    }
    dfs(1, 0);
    cout<<answer;
}