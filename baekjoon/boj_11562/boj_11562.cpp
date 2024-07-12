/**
 * @file 시간초과_boj_11562.cpp
 * @brief 백준 gold3 백양로 브레이크
 * @version 0.1
 * @date 2024-07-12
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>

#define INF 987654321

using namespace std;

int node_cnt, edge_cnt, question_cnt;
vector<vector<int> > costs;

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>node_cnt>>edge_cnt;
    costs.resize(node_cnt + 1, vector<int>(node_cnt + 1, INF));
    for(int i=0; i<edge_cnt; i++) {
        int src, dest, two_way; cin>>src>>dest>>two_way;
        costs[src][dest] = 0;
        costs[dest][src] = (two_way == 1) ? 0 : 1;
    }

    for(int i=1; i<=node_cnt; i++) costs[i][i] = 0;
    for(int i=1; i<=node_cnt; i++) {
        for(int j=1; j<=node_cnt; j++) {
            for(int k=1; k<=node_cnt; k++) {
                costs[j][k] = min(costs[j][k], costs[j][i] + costs[i][k]);
            }
        }
    }

    cin>>question_cnt;
    for(int i=0; i<question_cnt; i++) {
        int start, end; cin>>start>>end;
        cout<<costs[start][end]<<"\n";
    }
}