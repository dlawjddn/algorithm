#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

#define INF 987654321

using namespace std;

struct Info {
    int node, cost;
};
struct Path {
    int node, transfer, cost;
    bool operator<(Path other) const {
        if (transfer == other.transfer) return cost > other.cost;
        return transfer > other.transfer;
    }
};
int node_cnt, target;
vector<bool> company_info;
vector<pair<int, int> > visited;
vector<vector<Info> > maps;

void init() {
    maps.resize(node_cnt);
    visited.resize(node_cnt, {INF, INF});
}

void dijkstra() {
    priority_queue<Path> pq;
    pq.push({0, 0, 0});
    visited[0] = {0, 0};
    while(!pq.empty()) {
        auto[node, transfer, cost] = pq.top(); pq.pop();
        if (visited[node].first < transfer || (visited[node].first == transfer && visited[node].second < cost)) {
            continue;
        }
        for(int x=0; x<maps[node].size(); x++) {
            auto[nnode, add_cost] = maps[node][x];
            int ntransfer = (company_info[node] != company_info[nnode]) ? transfer + 1 : transfer;
            int ncost = cost + add_cost;
            if (visited[nnode].first > ntransfer || (visited[nnode].first == ntransfer && visited[nnode].second > ncost)) {
                pq.push({nnode, ntransfer, ncost});
                visited[nnode] = {ntransfer, ncost};
            }
        }
    }
}

int main() {
    cin>>node_cnt>>target;
    init();
    for(int i=0; i<node_cnt; i++) {
        int company; cin>>company;
        company_info.push_back((bool) company);
    }

    for(int y=0; y<node_cnt; y++) {
        for(int x=0; x<node_cnt; x++) {
            int cost; cin>>cost;
            if (cost == 0) continue;
            maps[y].push_back({x, cost});
            maps[x].push_back({y, cost});
        }
    }
    dijkstra();
    cout<<visited[target].first<<" "<<visited[target].second;
}