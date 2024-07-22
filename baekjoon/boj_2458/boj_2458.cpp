/**
 * @file boj_2458.cpp
 * @brief 백준 gold4 키 순서
 * @version 0.1
 * @date 2024-07-22
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int node_cnt, edge_cnt;
vector<vector<int> > infos;

int main(){
    cin>>node_cnt>>edge_cnt;
    infos.resize(node_cnt + 1, vector<int>(node_cnt + 1, -1));
    for(int i=1; i<=node_cnt; i++) infos[i][i] = 0; 
    for(int i=0; i<edge_cnt; i++) {
        int node1, node2; cin>>node1>>node2;
        infos[node1][node2] = 2;
        infos[node2][node1] = 1;
    }
    for(int i=1; i<=node_cnt; i++) {
        for(int j=1; j<=node_cnt; j++) {
            for(int k=1; k<=node_cnt; k++) {
                if (infos[j][i] == -1 || infos[i][k] == -1) continue;
                if (infos[j][i] == infos[i][k]) infos[j][k] = infos[j][i];
            }
        }
    }
    int answer = 0;
    for(int y=1; y<=node_cnt; y++) {
        int taller = 0, lower = 0;
        for(int x=1; x<=node_cnt; x++) {
            if (infos[y][x] == 1) taller++;
            else if (infos[y][x] == 2) lower++;
        }
        if ((taller + lower) == node_cnt - 1) answer++;
    }
    cout<<answer;
}