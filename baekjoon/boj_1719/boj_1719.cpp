/**
 * @file boj_1719.cpp
 * @brief 백준 gold3 택배
 * @version 0.1
 * @date 2024-07-13
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
vector<vector<int> > costs;
vector<vector<int> > results;

void print_result() {
    for(int y=1; y<=node_cnt; y++) {
        for(int x=1; x<=node_cnt; x++) {
            if (y == x) cout<<"- ";
            else cout<<results[y][x]<<" ";
        }
        cout<<"\n";
    }
}

int main(){
    cin>>node_cnt>>edge_cnt;
    costs.resize(node_cnt + 1, vector<int>(node_cnt + 1, INF));
    results.resize(node_cnt + 1, vector<int>(node_cnt + 1, -1)); 

    for(int i=1; i<=node_cnt; i++) {
        costs[i][i] = 0;
        results[i][i] = 0;
    }

    for(int i=0; i<edge_cnt; i++) {
        int node1, node2, cost; cin>>node1>>node2>>cost;
        if (costs[node1][node2] > cost) {
            costs[node1][node2] = cost;
            results[node1][node2] = node2;
        }
        if (costs[node2][node1] > cost) {
            costs[node2][node1] = cost;
            results[node2][node1] = node1;
        }
    }

    for(int i=1; i<=node_cnt; i++) {
        for(int j=1; j<=node_cnt; j++) {
            for(int k=1; k<=node_cnt; k++) {
                if (costs[j][k] > costs[j][i] + costs[i][k]) {
                    costs[j][k] = costs[j][i] + costs[i][k];
                    if (i != j) results[j][k] = results[j][i];
                }
            }
        }
    }

    print_result();
}
