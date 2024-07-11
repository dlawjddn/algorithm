/**
 * @file boj_14938.cpp
 * @brief 백준 gold4 서강그라운드
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

int node_cnt, limit, edge_cnt;
vector<int> items;
vector<vector<int> > costs;

int main(){
    cin>>node_cnt>>limit>>edge_cnt;
    items.resize(node_cnt + 1);
    costs.resize(node_cnt + 1, vector<int>(node_cnt + 1, INF));
    for(int i=1; i<=node_cnt; i++) {
        cin>>items[i];
        costs[i][i] = 0;
    }
    for(int i=0; i<edge_cnt; i++) {
        int node1, node2, cost; cin>>node1>>node2>>cost;
        costs[node1][node2] = min(costs[node1][node2], cost);
        costs[node2][node1] = min(costs[node2][node1], cost);
    }
    for(int i=1; i<=node_cnt; i++) {
        for(int j=1; j<=node_cnt; j++) {
            for(int k=1; k<=node_cnt; k++) {
                costs[j][k] = min(costs[j][k], costs[j][i] + costs[i][k]);
            }
        }
    }
    int answer = 0;
    for(int y=1; y<=node_cnt; y++) {
        int temp = 0;
        for(int x=1; x<=node_cnt; x++) {
            if (costs[y][x] <= limit) temp += items[x];
        }
        answer = max(answer, temp);
    }
    cout<<answer;
}