/**
 * @file boj_20183.cpp
 * @brief 백준 gold2 골목 대장 호석 - 효율성 2
 * @version 0.1
 * @date 2024-07-13
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

#define INF 99987654321

using namespace std;

struct Info{
    int pos;
    long long total_cost, max_cost;
    bool operator<(Info other) const {
        return max_cost > other.max_cost;
    }
};
int node_cnt, edge_cnt, spos, dpos;
long long budget;
vector<long long> max_costs;
vector<vector<pair<int, int> > > maps;

void print_costs() {
    for(int i=1; i<=node_cnt; i++) cout<<max_costs[i]<<" ";
    cout<<"\n";
}

Info make_info(int pos, long long total_cost, long long max_cost) {
    Info info;
    info.pos = pos;
    info.total_cost = total_cost;
    info.max_cost = max_cost;
    return info;
}

long long dijkstra() {
    priority_queue<Info> pq;
    pq.push(make_info(spos, 0, 0));
    max_costs[spos] = 0;
    while(!pq.empty()) {
        auto[pos, total_cost, max_cost] = pq.top(); pq.pop();
        if (max_costs[pos] != max_cost) continue;
        for(int x=0; x<maps[pos].size(); x++) {
            int npos = maps[pos][x].first;
            int ncost = maps[pos][x].second;
            long long ntotal_cost = total_cost + ncost;
            long long nmax_cost = max(max_cost, (long long)ncost);
            if (ntotal_cost > budget) continue;
            if (max_costs[npos] <= nmax_cost) continue;
            pq.push(make_info(npos, ntotal_cost, nmax_cost));
            max_costs[npos] = nmax_cost;
        }
    }
    if (max_costs[dpos] == INF) return -1;
    return max_costs[dpos];
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>node_cnt>>edge_cnt>>spos>>dpos>>budget;
    maps.resize(node_cnt + 1);
    max_costs.resize(node_cnt + 1, INF);
    for(int i=0; i<edge_cnt; i++) {
        int node1, node2, cost; cin>>node1>>node2>>cost;
        maps[node1].push_back(make_pair(node2, cost));
        maps[node2].push_back(make_pair(node1, cost));
    }
    cout<<dijkstra()<<"\n";
}