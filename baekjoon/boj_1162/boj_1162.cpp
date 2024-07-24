/**
 * @file boj_1162.cpp
 * @brief 백준 platium5 도로포장
 * @version 0.1
 * @date 2024-07-24
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <numeric>

#define INF 1e15

using namespace std;

struct Info {
    int pos, build;
    long long cost;

    bool operator<(Info other) const {
        return cost > other.cost;
    }
};
int node_cnt, edge_cnt, limit_build;
vector<vector<pair<int, int> > > maps;
vector<vector<long long> > visited;

Info make_info(int pos, int build, long long cost) {
    Info info;
    info.pos = pos;
    info.build = build;
    info.cost = cost;
    return info;
}

long long dijkstra() {
    priority_queue<Info> pq;
    pq.push(make_info(1, 0, 0));
    visited[1][0] = 0;
    while(!pq.empty()) {
        auto[pos, cnt, cost] = pq.top(); pq.pop();
        if (visited[pos][cnt] != cost) continue;
        for(int x=0; x<maps[pos].size(); x++) {
            auto[npos, add_cost] = maps[pos][x];
            long long normal_cost = cost + add_cost;
            int normal_cnt = cnt;
            long long build_cost = cost;
            int build_cnt = cnt + 1;

            if (visited[npos][normal_cnt] > normal_cost) {
                pq.push(make_info(npos, normal_cnt, normal_cost));
                visited[npos][normal_cnt] = normal_cost;
            }

            if (build_cnt > limit_build) continue;
            if (visited[npos][build_cnt] > build_cost) {
                pq.push(make_info(npos, build_cnt, build_cost));
                visited[npos][build_cnt] = build_cost;
            }
        }
    }
    return *min_element(visited[node_cnt].begin(), visited[node_cnt].end());
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>node_cnt>>edge_cnt>>limit_build;
    maps.resize(node_cnt + 1);
    visited.resize(node_cnt + 1, vector<long long>(limit_build + 1, INF));
    for(int i=0; i<edge_cnt; i++) {
        int node1, node2, cost; cin>>node1>>node2>>cost;
        maps[node1].push_back(make_pair(node2, cost));
        maps[node2].push_back(make_pair(node1, cost));
    }
    cout<<dijkstra();
}