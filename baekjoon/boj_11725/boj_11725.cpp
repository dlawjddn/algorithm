/**
 * @file boj_11725.cpp
 * @brief 백준 silver2 트리의 부모 찾기
 * @version 0.1
 * @date 2024-07-05
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include<iostream>
#include <vector>
#include <algorithm>

using namespace std;

int vertex_cnt;
vector<int> parents;
vector<vector<int> > maps;

void dfs(int pos) {
    for(int i=0; i<maps[pos].size(); i++) {
        int npos = maps[pos][i];
        if (parents[npos] != 0) continue;
        parents[npos] = pos;
        dfs(npos);
    }
}
int main(){
    cin>>vertex_cnt;
    parents.resize(vertex_cnt + 1, 0);
    maps.resize(vertex_cnt + 1, vector<int>());
    for(int i=0; i<vertex_cnt - 1; i++) {
        int node1, node2; cin>>node1>>node2;
        maps[node1].push_back(node2);
        maps[node2].push_back(node1);
    }
    parents[1] = 1;
    dfs(1);
    for(int i=2; i<=vertex_cnt; i++) cout<<parents[i]<<"\n";
}