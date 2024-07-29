/**
 * @file boj_13424.cpp
 * @brief 백준 gold4 비밀모임
 * @version 0.1
 * @date 2024-07-29
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

int node_cnt, edge_cnt, friend_cnt;
vector<vector<int> > dists;
vector<bool> friends(101, false);

int main(){
    int test_case; cin>>test_case;
    for(int t=0; t<test_case; t++) {
        cin>>node_cnt>>edge_cnt;
        dists = vector<vector<int> >(node_cnt + 1, vector<int>(node_cnt + 1, INF));
        for(int i=1; i<=node_cnt; i++) dists[i][i] = 0;
        for(int i=0; i<edge_cnt; i++) {
            int node1, node2, cost; cin>>node1>>node2>>cost;
            dists[node1][node2] = cost;
            dists[node2][node1] = cost;
        }
        cin>>friend_cnt; friends = vector<bool>(101, false);
        for(int i=0; i<friend_cnt; i++) {
            int idx; cin>>idx;
            friends[idx] = true;
        }
        for(int i=1; i<=node_cnt; i++) {
            for(int j=1; j<=node_cnt; j++) {
                for(int k=1; k<=node_cnt; k++) {
                    dists[j][k] = min(dists[j][k], dists[j][i] + dists[i][k]);
                }
            }
        }
        int min_value = INF, answer = 0;
        for(int room = 1; room <= node_cnt; room++) {
            int value = 0;
            for(int person = 1; person <= node_cnt; person++) {
                if (!friends[person]) continue;
                value += dists[room][person];
            }
            //cout<<"room: "<<room<<" value: "<<value<<"\n";
            if (value < min_value) {
                min_value = value;
                answer = room;
            }
        }
        cout<<answer<<"\n";
    }
}