/**
 * @file boj_2610.cpp
 * @author your name (you@domain.com)
 * @brief 백준 gold2 회의준비
 * @version 0.1
 * @date 2024-07-12
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

#define INF 987654321

using namespace std;

int node_cnt, edge_cnt;
vector<bool> visited;
vector<vector<int> > maps;
vector<vector<int> > group;
vector<vector<int> > costs;

vector<int> bfs(int spos) {
    vector<int> chosen;
    queue<int> q;
    q.push(spos);
    visited[spos] = true;
    while(!q.empty()) {
        int pos = q.front(); q.pop();
        chosen.push_back(pos);
        for(int x=0; x<maps[pos].size(); x++) {
            int npos = maps[pos][x];
            if (visited[npos]) continue;
            q.push(npos);
            visited[npos] = true;
        }
    }
    return chosen;
}

void make_group() {
    for(int i=1; i<=node_cnt; i++) {
        if (visited[i]) continue;
        group.push_back(bfs(i));
    }
}

int main(){
    cin>>node_cnt>>edge_cnt;
    maps.resize(node_cnt + 1);
    visited.resize(node_cnt + 1, false);
    costs.resize(node_cnt + 1, vector<int>(node_cnt + 1, INF));
    for(int i=0; i<edge_cnt; i++) {
        int node1, node2; cin>>node1>>node2;
        maps[node1].push_back(node2);
        maps[node2].push_back(node1);
        costs[node1][node2] = 1;
        costs[node2][node1] = 1;
    }
    // 위원회 묶기
    make_group();

    // 플로이드 워셜 진행
    for(int i=1; i<=node_cnt; i++) costs[i][i] = 0;
    for(int i=1; i<=node_cnt; i++) {
        for(int j=1; j<=node_cnt; j++) {
            for(int k=1; k<=node_cnt; k++) {
                costs[j][k] = min(costs[j][k], costs[j][i] + costs[i][k]);
            }
        }
    }

    // 위원회 대표 뽑기
    vector<int> leader;
    for(int i=0; i<group.size(); i++) {
        pair<int, int> result = make_pair(INF, -1);
        for(int j=0; j<group[i].size(); j++) {
            int leader = group[i][j], temp_max = 0;
            for(int k=0; k<group[i].size(); k++) {
                int me = group[i][k];
                temp_max = max(temp_max, costs[me][leader]);
            }
            if (result.first > temp_max) {
                result = make_pair(temp_max, leader);
            }
        }
        leader.push_back(result.second);
    }
    sort(leader.begin(), leader.end());

    // 결과 출력
    cout<<group.size()<<"\n";
    for(auto value : leader) cout<<value<<"\n";
}