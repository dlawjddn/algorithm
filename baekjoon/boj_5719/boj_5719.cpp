/**
 * @file boj_5719.cpp
 * @brief 백준 platium5 거의 최단 경로
 * @version 0.1
 * @date 2024-07-23
 * 
 * @copyright Copyright (c) 2024
 * 
 * 왜.. 시발..
 * 
 */
#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

const int INF = INT_MAX;
int node_cnt, edge_cnt, start, dest;
vector<vector<pair<int, int>>> maps;
vector<vector<pair<int, int>>> reverse_maps;
vector<int> costs;
vector<vector<bool>> is_shortest_path;

void dijkstra() {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    costs = vector<int>(node_cnt, INF);
    pq.push(make_pair(0, start));
    costs[start] = 0;
    while (!pq.empty()) {
        auto [cost, pos] = pq.top();
        pq.pop();
        if (costs[pos] < cost) continue;
        for (const auto& [npos, ncost] : maps[pos]) {
            int new_cost = cost + ncost;
            if (new_cost < costs[npos]) {
                pq.push(make_pair(new_cost, npos));
                costs[npos] = new_cost;
            }
        }
    }
}

void delete_edge() {
    queue<int> q;
    vector<bool> visited(node_cnt, false);
    q.push(dest);
    visited[dest] = true;
    while (!q.empty()) {
        int pos = q.front();
        q.pop();
        for (const auto& [bpos, cost] : reverse_maps[pos]) {
            if (costs[pos] == costs[bpos] + cost) {
                is_shortest_path[bpos][pos] = true;
                if (!visited[bpos]) {
                    q.push(bpos);
                    visited[bpos] = true;
                }
            }
        }
    }
}

int almost_shortest_path() {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<int> new_costs(node_cnt, INF);
    pq.push(make_pair(0, start));
    new_costs[start] = 0;
    while (!pq.empty()) {
        auto [cost, pos] = pq.top();
        pq.pop();
        if (new_costs[pos] < cost) continue;
        for (const auto& [npos, ncost] : maps[pos]) {
            if (is_shortest_path[pos][npos]) continue; // Skip shortest path edges
            int new_cost = cost + ncost;
            if (new_cost < new_costs[npos]) {
                pq.push(make_pair(new_cost, npos));
                new_costs[npos] = new_cost;
            }
        }
    }
    return new_costs[dest] == INF ? -1 : new_costs[dest];
}

int main() {
    while (cin >> node_cnt >> edge_cnt, node_cnt || edge_cnt) {
        cin >> start >> dest;
        maps.assign(node_cnt, vector<pair<int, int>>());
        reverse_maps.assign(node_cnt, vector<pair<int, int>>());
        is_shortest_path.assign(node_cnt, vector<bool>(node_cnt, false));
        for (int i = 0; i < edge_cnt; ++i) {
            int u, v, p;
            cin >> u >> v >> p;
            maps[u].emplace_back(v, p);
            reverse_maps[v].emplace_back(u, p);
        }
        dijkstra();
        delete_edge();
        cout << almost_shortest_path() << "\n";
    }
    return 0;
}
