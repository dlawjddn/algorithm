/**
 * @file boj_13907.cpp
 * @brief 백준 platium4 세금
 * @version 0.1
 * @date 2024-07-30
 * 
 * @copyright Copyright (c) 2024
 * 
 * 플레티넘 문제는 참 항상 신기하다.. 좀 더 잘 고민했으면 더 잘 풀었을거 같긴 하다..
 * 까비!
 */
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <numeric>

#define INF 987654321

using namespace std;

int node_cnt, edge_cnt, tax_cnt, start, dest, sum_tax;
vector<vector<pair<int, int> > > maps;
vector<vector<int> > visited;

pair<int, pair<int, int> > make_dpair(int cost, int pos, int cnt) {
    return make_pair(cost, make_pair(pos, cnt));
}

void dijkstra() {
    priority_queue<pair<int, pair<int, int> >, vector<pair<int, pair<int, int> > >, greater<pair<int, pair<int, int> > > > pq;
    pq.push(make_dpair(0, start, 0));
    visited[start][0] = 0;
    while(!pq.empty()) {
        auto[cost, info] = pq.top(); pq.pop();
        auto[pos, cnt] = info;
        if (visited[pos][cnt] != cost) continue;
        for(int x=0; x<maps[pos].size(); x++) {
            int npos = maps[pos][x].first;
            int ncost = cost + maps[pos][x].second;
            int ncnt = cnt + 1;
            if (visited[npos][ncnt] <= ncost || ncnt > node_cnt) continue;
            pq.push(make_dpair(ncost, npos, ncnt));
            visited[npos][ncnt] = ncost;
        }
    }
}

int after_increase() {
    int result = INF;
    for(int i=0; i<visited[dest].size(); i++) {
        result = min(result, visited[dest][i] + (i * sum_tax));
    }
    return result;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>node_cnt>>edge_cnt>>tax_cnt>>start>>dest;
    maps.resize(node_cnt + 1);
    visited.resize(node_cnt + 1, vector<int>(node_cnt + 1, INF));
    for(int i=0; i<edge_cnt; i++) {
        int node1, node2, cost; cin>>node1>>node2>>cost;
        maps[node1].push_back(make_pair(node2, cost));
        maps[node2].push_back(make_pair(node1, cost));
    }
    dijkstra();
    cout<<*min_element(visited[dest].begin(), visited[dest].end())<<"\n";
    for(int i=0; i<tax_cnt; i++) {
        int add_tax; cin>>add_tax;
        sum_tax += add_tax;
        cout<<after_increase()<<"\n";
    }
}