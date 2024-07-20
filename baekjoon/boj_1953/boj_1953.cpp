/**
 * @file boj_1953.cpp
 * @brief 백준 gold4 팀 배분
 * @version 0.1
 * @date 2024-07-20
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int node_cnt;
vector<bool> check;
vector<bool> visited;
vector<vector<int> > maps;

void bfs(int spos) {
    queue<int> q;
    q.push(spos);
    visited[spos] = true;
    check[spos] = true;
    while(!q.empty()) {
        int pos = q.front(); q.pop();
        for(int x=0; x<maps[pos].size(); x++) {
            int npos = maps[pos][x];
            if (visited[npos]) continue;
            q.push(npos);
            visited[npos] = true;
            check[npos] = !check[pos];
        }
    }
}

int main(){
    cin>>node_cnt;
    maps.resize(node_cnt + 1);
    check.resize(node_cnt + 1);
    visited.resize(node_cnt + 1, false);
    for(int i=1; i<=node_cnt; i++) {
        int hate_cnt; cin>>hate_cnt;
        for(int j=0; j<hate_cnt; j++) {
            int hate_person; cin>>hate_person;
            maps[i].push_back(hate_person);
            maps[hate_person].push_back(i);
        }
    }
    for(int i=1; i<=node_cnt; i++) {
        if (visited[i]) continue;
        bfs(i);
    }
    vector<int> blue;
    vector<int> white;
    for(int i=1; i<=node_cnt; i++) {
        if (check[i]) blue.push_back(i);
        else white.push_back(i);
    }
    cout<<blue.size()<<"\n";
    for(auto person : blue) cout<<person<<" ";
    cout<<"\n"<<white.size()<<"\n";
    for(auto person : white) cout<<person<<" ";
}

