#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

#define INF 987654321

using namespace std;

int node_cnt, edge_cnt;
vector<vector<int> > maps;
vector<int> visited;

void dijsktra() {
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
    pq.push({0, 1});
    visited[1] = 0;
    while(!pq.empty()) {
        auto[cost, pos] = pq.top(); pq.pop();
        if (visited[pos] < cost) continue;
        for(int x=0; x<maps[pos].size(); x++) {
            int npos = maps[pos][x];
            int ncost = cost + 1;
            if (visited[npos] <= ncost) continue;
            pq.push({ncost, npos});
            visited[npos] = ncost;
        }
    }
}

int main() {
    cin>>node_cnt>>edge_cnt;
    maps.resize(node_cnt + 1);
    visited.resize(node_cnt + 1, INF);
    for(int i=0; i<edge_cnt; i++) {
        int node1, node2; cin>>node1>>node2;
        maps[node1].push_back(node2);
        maps[node2].push_back(node1);
    }
    dijsktra();
    int answer_node = 1, answer_dist = 0, answer_cnt = 1;
    for(int i=1; i<=node_cnt; i++) {
        if (answer_dist <= visited[i]) {
            if (answer_dist == visited[i]) {
                answer_cnt++;
            } else {
                answer_node = i;
                answer_dist = visited[i];
                answer_cnt = 1;   
            }
        }
    }
    cout<<answer_node<<" "<<answer_dist<<" "<<answer_cnt;
}