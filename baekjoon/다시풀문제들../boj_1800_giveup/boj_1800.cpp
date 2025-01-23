/**
 * @file boj_1800.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-07-04
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <numeric>

#define INF 1000001

using namespace std;

struct Info {
    int bpos, pos, total_cost;
    vector<int> costs;

    bool operator<(Info other) const {
        return costs > other.costs;
    }
};
int node_cnt, line_cnt, free_cnt;
vector<vector<pair<int, int> > > maps(1001);
vector<vector<int> > visited;
vector<int> min_costs;

void print_visited() {
    for(int y=1; y<visited.size(); y++) {
        for(int x=1; x<visited[y].size(); x++) {
            cout<<visited[y][x]<<" ";
        }
        cout<<"\n";
    }
}

Info make_info(int bpos, int pos, int total_cost, vector<int> costs) {
    Info info;
    info.bpos = bpos;
    info.pos = pos;
    info.total_cost = total_cost;
    info.costs = costs;
    return info;
}

vector<int> make_next_vector(vector<int> costs, int ncost) {
    vector<int> next = costs;
    next.push_back(ncost);
    return next;
}

void dijsktra() {
    priority_queue<Info> pq;
    pq.push(make_info(0, 1, 0, vector<int>()));
    visited[0][1] = 0;
    while(!pq.empty()) {
        auto [bpos, pos, total_cost, costs] = pq.top(); pq.pop();
        if (visited[bpos][pos] != total_cost) continue;
        cout<<"check\n";
        //print_info(pos, total_cost, costs);
        if (pos == node_cnt) {
            sort(costs.begin(), costs.end());
            int before_sum = accumulate(min_costs.begin(), min_costs.end() - free_cnt, 0);
            int now_sum = accumulate(costs.begin(), costs.end() - free_cnt, 0);
            if (before_sum > now_sum) {
                min_costs = costs;
            }
        }
        for(int d=0; d<maps[pos].size(); d++) {
            int npos = maps[pos][d].first;
            int ncost = maps[pos][d].second;
            int ntotal_cost = ncost + total_cost;
            if (visited[pos][npos] <= ncost) continue;
            cout<<"push\n";
            pq.push(make_info(pos, npos, ntotal_cost, make_next_vector(costs, ncost)));
            visited[pos][npos] = ncost;
        }
    }
}

int main(){
    cin>>node_cnt>>line_cnt>>free_cnt;
    min_costs.resize(node_cnt + 1, INF);
    visited.resize(node_cnt + 1, vector<int>(node_cnt + 1, INF));
    for(int i=0; i<line_cnt; i++) {
        int src, dest, cost; cin>>src>>dest>>cost;
        maps[src].push_back(make_pair(dest, cost));
        maps[dest].push_back(make_pair(src, cost));
    }
    dijsktra();
    print_visited();
}