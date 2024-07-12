/**
 * @file 시간초과_boj_11562.cpp
 * @brief 백준 gold3 백양로 브레이크
 * @version 0.1
 * @date 2024-07-12
 * 
 * @copyright Copyright (c) 2024
 * 
 * 이게 왜 플로이드-워셜인지 이제 보이는걸까.. 너무 잘 보이는 문제인데.. 하..
 * 최단경로만 보면.. 왜 다익스트라 밖에 생각이 안 날까..
 * 각 질문에 대해서 모두 다익스트라를 하면 무조건 시간초과가 발생할 수 밖에 없는 문제..
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

#define INF 987654321

using namespace std;

int node_cnt, edge_cnt, question_cnt;
vector<int> visited;
vector<vector<pair<int, int> > > maps;

int dijkstra(int start, int end) {
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
    pq.push(make_pair(0, start));
    visited[start] = 0;
    while(!pq.empty()) {
        auto[change, pos] = pq.top(); pq.pop();
        if (visited[pos] != change) continue;
        for(int x=0; x<maps[pos].size(); x++) {
            auto[npos, available] = maps[pos][x];
            int nchange = change;
            if (!available) nchange++;
            if (visited[npos] <= nchange) continue;
            pq.push(make_pair(nchange, npos));
            visited[npos] = nchange;
        }
    }
    return visited[end];
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>node_cnt>>edge_cnt;
    maps.resize(node_cnt + 1, vector<pair<int, int> >(node_cnt + 1));
    for(int i=0; i<edge_cnt; i++) {
        int src, dest, two_way; cin>>src>>dest>>two_way;
        maps[src].push_back(make_pair(dest, 1));
        if (two_way) maps[dest].push_back(make_pair(src, 1));
        else maps[dest].push_back(make_pair(src, 0));
    }
    cin>>question_cnt;
    for(int i=0; i<question_cnt; i++) {
        visited = vector<int>(node_cnt + 1, INF);
        int start, end; cin>>start>>end;
        cout<<dijkstra(start, end)<<"\n";
    }
}