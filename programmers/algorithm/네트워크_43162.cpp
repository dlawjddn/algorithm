#include <string>
#include <vector>
#include <iostream>

using namespace std;

vector<int> visited(201, 0);

void print_visited(int n){
    for(int i=0; i<n; i++){
        cout<<visited[i]<<" ";
    }
    cout<<"\n";
}

void dfs(vector<vector<int> > computers, int pos, int network){
    visited[pos] = network;
    for(int i=0; i<computers[pos].size(); i++){
        if (pos == i || visited[i] || computers[pos][i] == 0) continue;
        dfs(computers, i, network);
    }
}

int solution(int n, vector<vector<int>> computers) {
    int answer = 0;
    for(int i=0; i<n; i++){
        if (visited[i]) continue;
        ++answer;
        dfs(computers, i, answer);
    }
    //print_visited(n);
    return answer;
}
/**
 * @file 네트워크_43162.cpp
 * @brief 프로그래머스 lv.3 네트워크
 * @version 0.1
 * @date 2024-08-17
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <string>
#include <vector>
#include <iostream>

using namespace std;

int node_cnt = 0;
vector<vector<int> > maps;
vector<int> groups;

void print_groups() {
    for(int i=1; i<=node_cnt; i++) {
        cout<<groups[i]<<" ";
    }
    cout<<"\n";
}

void dfs(int pos, int group_num) {
    groups[pos] = group_num;
    for(int x=0; x<maps[pos].size(); x++) {
        int npos = maps[pos][x];
        if (groups[npos] != 0) continue;
        dfs(npos, group_num);
    }
}

int solution(int n, vector<vector<int>> computers) {
    int group_cnt = 0;
    node_cnt = n;
    maps.resize(n+1);
    groups.resize(n+1, 0);
    for(int i=0; i<computers.size(); i++) {
        for(int j=0; j<computers[i].size(); j++) {
            if (i == j || computers[i][j] == 0) continue;
            maps[i+1].push_back(j+1);
        }
    }
    for(int i=1; i<=n; i++) {
        if (groups[i] != 0) continue;
        dfs(i, ++group_cnt);
    }
    print_groups();
    return group_cnt;
}