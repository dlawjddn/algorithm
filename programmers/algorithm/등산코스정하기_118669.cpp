/**
 * @file 등산코스정하기_118669.cpp
 * @brief 프로그래머스 lv.3 카카오 2022 인턴십 등산코스 정하기
 * @version 0.1
 * @date 2024-08-21
 * 
 * @copyright Copyright (c) 2024
 * 
 * 1. 문제 조건 잘 읽기.. -> 같은 비용이 드는 경우에는 산봉우리가 작은 걸로 선택한다.
 * 2. 따라서 같은 비용이 드는 경우도 있기 때문에 다익스트라 중 정답이 되는 비용과 같은 비용은 유효한 비용이 된다
 * 
 */
#include <string>
#include <vector>
#include <algorithm>
#include <queue>

#define INF 987654321

using namespace std;

int node_cnt = 0;
int destination = 0, intensity = INF;
vector<bool> check_summits(100001, false);
vector<vector<pair<int, int> > > maps;

vector<int> dijkstra(int spos) {
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
    vector<int> visited(node_cnt + 1, INF);
    pq.push({0, spos});
    visited[spos] = 0;
    while(!pq.empty()) {
        auto[max_cost, pos] = pq.top(); pq.pop();
        if (check_summits[pos]) continue;
        if (visited[pos] != max_cost) continue;
        for(int x=0; x<maps[pos].size(); x++) {
            auto[npos, cost] = maps[pos][x];
            int nmax_cost = max(max_cost, cost);
            if (visited[npos] <= nmax_cost || intensity <= nmax_cost) continue;
            pq.push({nmax_cost, npos});
            visited[npos] = nmax_cost;
        }
    }
    return visited;
}

vector<int> solution(int n, vector<vector<int>> paths, vector<int> gates, vector<int> summits){
    node_cnt = n;
    maps.resize(n+1);
    sort(summits.begin(), summits.end());
    for(auto summit : summits) check_summits[summit] = true;
    for(auto path : paths) {
        int node1 = path[0];
        int node2 = path[1];
        int cost = path[2];
        maps[node1].push_back({node2, cost});
        maps[node2].push_back({node1, cost});
    }
    for(auto gate : gates) {
        vector<int> visited = dijkstra(gate);
        for(auto summit : summits) {
            if (visited[summit] == INF) continue;
            if (visited[summit] < intensity) {
                destination = summit;
                intensity = visited[summit];
            } else if (visited[summit] == intensity) {
                destination = min(destination, summit);
            }
        }
    }
    return {destination, intensity};
}