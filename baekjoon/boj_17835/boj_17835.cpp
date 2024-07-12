/**
 * @file boj_17835.cpp
 * @brief 백준 gold2 면접 보는 승범이네
 * @version 0.1
 * @date 2024-07-13
 * 
 * @copyright Copyright (c) 2024
 * 
 * 오.. 시작점이 여러 개 일때도 시작점 마다 다익스트라를 하는게 아니라
 * 처음에 enqueue를 할 때, 시작점에 대해서 모두 적용을 해주면 되는구나! 
 * 
 * 다익스트라도 똑같군..
 * 
 * 그래도 다양한 시작점에서 특정 도착점이라면 역방향으로 입력을 받아서 특정 도착점에서 시작점을 가는 최소 비용을 구하는 방법을 적용했다. 
 * 공부한 보람이 없지는 않넹.. ㅎㅎ ㅠ
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

#define INF 99987654321

using namespace std;

int node_cnt, edge_cnt, dest_cnt;
vector<int> destinations;
vector<vector<pair<int, int> > > maps;
vector<long long> costs;

void dijkstra() {
    priority_queue<pair<long long, int>, vector<pair<long long, int> >, greater<pair<long long, int> > > pq;
    for(auto dest : destinations) {
        pq.push(make_pair(0, dest));
        costs[dest] = 0;
    }
    while(!pq.empty()) {
        auto[cost, pos] = pq.top(); pq.pop();
        if (costs[pos] != cost) continue;
        for(int x=0; x<maps[pos].size(); x++) {
            int npos = maps[pos][x].first;
            long long ncost = cost + (long long)maps[pos][x].second;
            if (costs[npos] <= ncost) continue;
            pq.push(make_pair(ncost, npos));
            costs[npos] = ncost;
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>node_cnt>>edge_cnt>>dest_cnt;
    maps.resize(node_cnt + 1);
    costs.resize(node_cnt + 1, INF);
    destinations.resize(dest_cnt);
    for(int i=0; i<edge_cnt; i++) {
        int src, dest, cost; cin>>src>>dest>>cost;
        maps[dest].push_back(make_pair(src, cost));
    }
    for(int i=0; i<dest_cnt; i++) {
        cin>>destinations[i];
    }
    dijkstra();
    pair<int, long long> result = make_pair(-1, -1);
    for(int person = 1; person<=node_cnt; person++) {
        if (result.second < costs[person]) {
            result = make_pair(person, costs[person]);
        }
    }
    cout<<result.first<<"\n"<<result.second;
}
