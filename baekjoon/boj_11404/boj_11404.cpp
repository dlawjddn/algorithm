/**
 * @file boj_11404.cpp
 * @brief 백준 gold4 플로이드
 * @version 0.1
 * @date 2024-07-07
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>

#define INF 987654321

using namespace std;

int node_cnt, edge_cnt;
vector<vector<int> > maps;

int main(){
    cin>>node_cnt>>edge_cnt;
    maps.resize(node_cnt + 1, vector<int>(node_cnt + 1, INF));
    // 본인이 본인에게 가는 비용은 0
    for(int i=1; i<=node_cnt; i++) maps[i][i] = 0;

    // 간선 중 최소값으로 업데이트
    for(int i=0; i<edge_cnt; i++) {
        int src, dest, cost; cin>>src>>dest>>cost;
        maps[src][dest] = min(maps[src][dest], cost);
    }

    // 플로이드 와샬
    for(int i=1; i<=node_cnt; i++) {
        for(int y=1; y<=node_cnt; y++) {
            for(int x=1; x<=node_cnt; x++) {
                maps[y][x] = min(maps[y][x], maps[y][i] + maps[i][x]);
            }
        }
    }

    for(int y=1; y<=node_cnt; y++) {
        for(int x=1; x<=node_cnt; x++) {
            if (maps[y][x] == INF) cout<<"0 ";
            else cout<<maps[y][x]<<" ";
        }
        cout<<"\n";
    }

}