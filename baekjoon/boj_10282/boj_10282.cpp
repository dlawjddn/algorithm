/**
 * @file boj_10282.cpp
 * @brief 백준 gold4 해킹
 * @version 0.1
 * @date 2024-07-17
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

#define INF 987654321

using namespace std;

int node_cnt, edge_cnt, hacked;
vector<vector<pair<int, int> > > maps;

void dijkstra() {
    int cnt = 0, total_times = 0;
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
    vector<int> visited(node_cnt + 1, INF);
    pq.push(make_pair(0, hacked));
    visited[hacked] = 0;
    while(!pq.empty()) {
        auto[seconds, pos] = pq.top(); pq.pop();
        if (visited[pos] != seconds) continue;
        cnt++;
        total_times = max(total_times, seconds);
        for(int x=0; x<maps[pos].size(); x++) {
            int npos = maps[pos][x].first;
            int nseconds = seconds + maps[pos][x].second;
            if (visited[npos] <= nseconds) continue;
            pq.push(make_pair(nseconds, npos));
            visited[npos] = nseconds;
        }
    }
    cout<<cnt<<" "<<total_times<<"\n";
}

int main(){
    int test_case; cin>>test_case;
    for(int t=0; t<test_case; t++) {
        cin>>node_cnt>>edge_cnt>>hacked;
        maps = vector<vector<pair<int, int> > >(node_cnt + 1);
        for(int i=0; i<edge_cnt; i++) {
            int child, parent, seconds; cin>>child>>parent>>seconds;
            maps[parent].push_back(make_pair(child, seconds));
        }
        dijkstra();
    }
}