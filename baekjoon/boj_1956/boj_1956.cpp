/**
 * @file boj_1956.cpp
 * @brief 백준 gold4 운동
 * @version 0.1
 * @date 2024-07-22
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
vector<vector<int> > costs;

int main(){
    cin>>node_cnt>>edge_cnt;
    costs.resize(node_cnt + 1, vector<int>(node_cnt + 1, INF));
    for(int i=0; i<edge_cnt; i++) {
        int start, end, cost; cin>>start>>end>>cost;
        costs[start][end] = min(costs[start][end], cost);
    }
    for(int i=1; i<=node_cnt; i++) costs[i][i] = 0;
    for(int i=1; i<=node_cnt; i++) {
        for(int j=1; j<=node_cnt; j++) {
            for(int k=1; k<=node_cnt; k++) {
                costs[j][k] = min(costs[j][k], costs[j][i] + costs[i][k]);
            }
        }
    }
    int answer = INF;
    for(int y=1; y<=node_cnt; y++) {
        for(int x=1; x<=node_cnt; x++) {
            if (y == x) continue;
            if (costs[y][x] == INF || costs[x][y] == INF) continue;
            answer = min(answer, costs[y][x] + costs[x][y]);
        }
    }
    cout<<((answer == INF) ? -1 : answer);
}