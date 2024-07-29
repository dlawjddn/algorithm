/**
 * @file boj_16118.cpp
 * @brief 백준 gold1 달빛 여우
 * @version 0.1
 * @date 2024-07-29
 * 
 * @copyright Copyright (c) 2024
 * 
 * 골드1 원트 컷~!
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

#define INF 987654321

using namespace std;

int node_cnt, edge_cnt;
vector<vector<pair<int, int> > > maps;
vector<int> visited_fox;
vector<double> visited_wolf;

void print_visited() {
    for(int i=1; i<=node_cnt; i++) cout<<visited_fox[i]<<" ";
    cout<<"\n";
    for(int i=1; i<=node_cnt; i++) cout<<visited_wolf[i]<<" ";
    cout<<"\n";
}

vector<int> fox_dijkstra() {
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
    vector<int> visited(node_cnt + 1, INF);
    pq.push(make_pair(0, 1));
    visited[1] = 0;
    while(!pq.empty()) {
        auto[cost, pos] = pq.top(); pq.pop();
        if (visited[pos] != cost) continue;
        for(int x=0; x<maps[pos].size(); x++) {
            int npos = maps[pos][x].first;
            int ncost = cost + maps[pos][x].second;
            if (visited[npos] <= ncost) continue;
            pq.push(make_pair(ncost, npos));
            visited[npos] = ncost;
        }
    }
    return visited;
}

pair<double, pair<int, bool> > make_dpair(double cost, int pos, bool fast) {
    return make_pair(cost, make_pair(pos, fast));
}

vector<double> wolf_dijkstra() {
    priority_queue<pair<double, pair<int, bool> >, vector<pair<double, pair<int, bool> > >, greater<pair<double, pair<int, bool> > > > pq;
    vector<vector<double> > visited(node_cnt + 1, vector<double>(2, INF));
    pq.push(make_dpair(0.0, 1, true));
    visited[1][0] = 0.0;
    while(!pq.empty()) {
        auto[cost, info] = pq.top(); pq.pop();
        int pos = info.first;
        bool fast = info.second;
        //cout<<pos<<" "<<cost<<"\n";
        if (visited[pos][!fast] != cost) continue;
        for(int x=0; x<maps[pos].size(); x++) {
            int npos = maps[pos][x].first;
            double ncost = (fast) ? cost + maps[pos][x].second / 2.0 : cost + maps[pos][x].second * 2.0;
            int nfast = !fast;
            if (visited[npos][fast] <= ncost) continue;
            pq.push(make_dpair(ncost, npos, nfast));
            visited[npos][fast] = ncost;
        }
    }
    vector<double> result(node_cnt + 1, INF);
    for(int i=1; i<=node_cnt; i++) result[i] = min(visited[i][0], visited[i][1]);
    return result;
}

int main(){
    cin>>node_cnt>>edge_cnt;
    maps.resize(node_cnt + 1);
    for(int i=0; i<edge_cnt; i++) {
        int node1, node2, cost; cin>>node1>>node2>>cost;
        maps[node1].push_back(make_pair(node2, cost));
        maps[node2].push_back(make_pair(node1, cost));
    }
    visited_fox = fox_dijkstra();
    visited_wolf = wolf_dijkstra();
    int answer = 0;
    for(int i=1; i<=node_cnt; i++) {
        if (visited_fox[i] < visited_wolf[i]) answer++;
    }
    cout<<answer;
}