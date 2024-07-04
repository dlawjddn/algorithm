/**
 * @file boj_11779.cpp
 * @brief 백준 gold3 최소비용 구하기 2
 * @version 0.1
 * @date 2024-07-05
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include<iostream>
#include <vector>
#include <algorithm>
#include <queue>

#define INF 987654321

using namespace std;

struct Info {
    int pos, cost;
    vector<int> path;

    bool operator<(Info other) const {
        return cost > other.cost;
    }
};
int vertex_cnt, edge_cnt, start, destination;
vector<int> answer;
vector<int> visited;
vector<vector<pair<int, int> > > maps;

Info make_info(int pos, int cost, vector<int> path) {
    Info info;
    info.pos = pos;
    info.cost = cost;
    info.path = path;
    return info;
}

vector<int> next_path(vector<int> path, int num) {
    vector<int> next_path = path;
    next_path.push_back(num);
    return next_path;
}

void dijkstra() {
    priority_queue<Info> pq;
    pq.push(make_info(start, 0, next_path(vector<int>(), start)));
    visited[start] = 0;
    while(!pq.empty()) {
        auto[pos, cost, path] = pq.top(); pq.pop();
        if (visited[pos] != cost) continue;
        if (pos == destination) {
            answer = path;
        }
        for(int x=0; x<maps[pos].size(); x++) {
            int npos = maps[pos][x].first;
            int ncost = cost + maps[pos][x].second;
            if (visited[npos] <= ncost) continue;
            pq.push(make_info(npos, ncost, next_path(path, npos)));
            visited[npos] = ncost;
        }
    }
    cout<<visited[destination]<<"\n"<<answer.size()<<"\n";
    for(auto path : answer) cout<<path<<" ";
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>vertex_cnt>>edge_cnt;
    visited.resize(vertex_cnt + 1, INF);
    maps.resize(vertex_cnt + 1, vector<pair<int, int> >());
    for(int i=0; i<edge_cnt; i++) {
        int src, dest, cost; cin>>src>>dest>>cost;
        maps[src].push_back(make_pair(dest, cost));
    }
    cin>>start>>destination;
    dijkstra();
}