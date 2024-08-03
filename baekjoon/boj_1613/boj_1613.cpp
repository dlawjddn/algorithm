/**
 * @file boj_1613.cpp
 * @brief 백준 gold3 역사
 * @version 0.1
 * @date 2024-08-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int node_cnt, edge_cnt, question_cnt;
vector<vector<int> > infos;

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>node_cnt>>edge_cnt;
    infos.resize(node_cnt + 1, vector<int>(node_cnt + 1, 0));
    for(int i=0; i<edge_cnt; i++) {
        int node1, node2; cin>>node1>>node2;
        infos[node1][node2] = -1;
        infos[node2][node1] = 1;
    }
    for(int i=1; i<=node_cnt; i++) {
        for(int j=1; j<=node_cnt; j++) {
            for(int k=1; k<=node_cnt; k++) {
                if ((infos[j][i] != 0 && infos[i][k] != 0) && infos[j][i] == infos[i][k]) infos[j][k] = infos[j][i];
            }
        }
    }
    cin>>question_cnt;
    for(int i=0; i<question_cnt; i++) {
        int node1, node2; cin>>node1>>node2;
        cout<<infos[node1][node2]<<"\n";
    }
}