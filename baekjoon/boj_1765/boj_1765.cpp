/**
 * @file boj_1765.cpp
 * @brief 백준 gold2 닭싸움 팀 정하기
 * @version 0.1
 * @date 2024-08-02
 * 
 * @copyright Copyright (c) 2024
 * 
 * 유니온 파인드와 이분그래프의 응용!!! 굿~!
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int node_cnt, edge_cnt, start = 0;
vector<int> parents;
vector<int> blue_team;
vector<int> red_team;
vector<bool> checked;
vector<vector<int> > maps;

int find_parent(int node) {
    if (node == parents[node]) return node;
    return parents[node] = find_parent(parents[node]);
}

void make_union(int parent, int child) {
    parent = find_parent(parent);
    child = find_parent(child);
    if (parent > child) parents[parent] = child;
    else parents[child] = parent;
}

bool is_same_parent(int node1, int node2) {
    int n1p = find_parent(node1);
    int n2p = find_parent(node2);
    if (n1p == n2p) return true;
    return false;
}

void binary_graph() {
    if (start == 0) return ;
    queue<pair<int, bool> > q;
    vector<bool> visited(node_cnt + 1, false);
    q.push({start, true});
    blue_team.push_back(start);
    visited[start] = true;
    while(!q.empty()) {
        auto[pos, team] = q.front(); q.pop();
        for(int x=0; x<maps[pos].size(); x++) {
            int npos = maps[pos][x];
            bool nteam = !team;
            if (visited[npos]) continue;
            q.push({npos, nteam});
            visited[npos] = true;
            if (nteam) blue_team.push_back(npos);
            else red_team.push_back(npos);
        }
    }
}

int main(){
    cin>>node_cnt>>edge_cnt;
    maps.resize(node_cnt + 1);
    checked.resize(node_cnt + 1, false);
    parents.resize(node_cnt + 1);
    for(int i=1; i<=node_cnt; i++) parents[i] = i;
    for(int i=0; i<edge_cnt; i++) {
        char info;
        int node1, node2; cin>>info>>node1>>node2;
        if (info == 'E') {
            if (start == 0) start = node1;
            maps[node1].push_back(node2);
            maps[node2].push_back(node1);
        } else {
            if (is_same_parent(node1, node2)) continue;
            make_union(node1, node2);
        }
    }
    binary_graph();
    for(int i=1; i<red_team.size(); i++) {
        int node1 = red_team[i-1];
        int node2 = red_team[i];
        if (is_same_parent(node1, node2)) continue;
        make_union(node1, node2);
    }
    for(int i=1; i<blue_team.size(); i++) {
        int node1 = blue_team[i-1];
        int node2 = blue_team[i];
        if (is_same_parent(node1, node2)) continue;
        make_union(node1, node2);
    }
    int answer = 0;
    for(int i=1; i<=node_cnt; i++) {
        int leader = find_parent(i);
        if (checked[leader]) continue;
        answer++;
        checked[leader] = true;
    }
    cout<<answer;
}