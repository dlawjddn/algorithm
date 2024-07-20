/**
 * @file boj_1707.cpp
 * @brief 백준 gold4 이분그래프
 * @version 0.1
 * @date 2024-07-20
 * 
 * @copyright Copyright (c) 2024
 * 
 * 이분그래프에 대해서 알게 된 문제
 * 
 * 이분그래프란?
 * - 한 정점이 빨간색으로 칠할 때 그 정점과 연결된 정점들은 파란색으로 칠한다는 조건을 생각하면 이해가 쉬워진다. 
 *   이분 그래프의 요점은 한 정점과 그 정점과 연결된 노드들은 다른 색깔로 칠할 때 모든 노드들이 2가지 색으로 구별되며
 *   연결된 정점들은 모두 색이 다른 색으로 연결되어야 한다는 점이다. 
 * 
 * 이분그래프가 의미하는 바를 이해하면 쉬웠던 문제!
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int node_cnt, edge_cnt;
vector<vector<int> > maps;
vector<bool> check;
vector<bool> visited;

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
            check[npos] = !check[pos];
            visited[npos] = true;
        }
    }
}

bool binary_graph() {
    for(int i=1; i<=node_cnt; i++) {
        bool status = check[i];
        for(int j=0; j<maps[i].size(); j++) {
            bool compare = check[maps[i][j]];
            if (status == compare) return false;
        }
    }
    return true;
}

int main(){
    int test_case; cin>>test_case;
    for(int i=0; i<test_case; i++) {
        cin>>node_cnt>>edge_cnt;
        maps = vector<vector<int> > (node_cnt + 1);
        check = vector<bool>(node_cnt + 1);
        visited = vector<bool>(node_cnt + 1, false);
        for(int j=0; j<edge_cnt; j++) {
            int node1, node2; cin>>node1>>node2;
            maps[node1].push_back(node2);
            maps[node2].push_back(node1);
        }
        for(int j=1; j<=node_cnt; j++) {
            if (visited[j]) continue;
            bfs(j);
        }
        cout<<((binary_graph()) ? "YES\n" : "NO\n");
    }
}