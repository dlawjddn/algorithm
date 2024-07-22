/**
 * @file boj_1854.cpp
 * @brief 백준 platium4 K번째 최단경로
 * @version 0.1
 * @date 2024-07-22
 * 
 * @copyright Copyright (c) 2024
 * 
 * 와.. 이걸 이렇게 생각할 수 있다는게 소름이다.. 기존 다익스트라의 틀을 깬 문제..
 * 좋은 문제인거 같다..
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int node_cnt, edge_cnt, k;
vector<vector<pair<int, int> > > maps;
vector<vector<int> > costs;

void dijkstra() {
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
    pq.push(make_pair(0, 1));
    costs[1].push_back(0);
    while(!pq.empty()) {
        auto[cost, pos] = pq.top(); pq.pop();
        for(int x=0; x<maps[pos].size(); x++) {
            int npos = maps[pos][x].first;
            int ncost = cost + maps[pos][x].second;
            if (costs[npos].size() < k) {
                pq.push(make_pair(ncost, npos));
                costs[npos].push_back(ncost);
                sort(costs[npos].begin(), costs[npos].end());
            }
            else {
                if (ncost < costs[npos].back()) {
                    pq.push(make_pair(ncost, npos));
                    costs[npos].pop_back();
                    costs[npos].push_back(ncost);
                    sort(costs[npos].begin(), costs[npos].end());
                }
            }
        }
    }
}

int main(){
    cin>>node_cnt>>edge_cnt>>k;
    maps.resize(node_cnt + 1);
    costs.resize(node_cnt + 1);
    for(int i=0; i<edge_cnt; i++) {
        int start, end, cost; cin>>start>>end>>cost;
        maps[start].push_back(make_pair(end, cost));
    }
    dijkstra();
    for(int i=1; i<=node_cnt; i++) {
        if (costs[i].size() < k) cout<<"-1\n";
        else cout<<costs[i][k-1]<<"\n";
    }
}