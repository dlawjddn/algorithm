/**
 * @file boj_13911.cpp
 * @brief 백준 gold2 집 구하기
 * @version 0.1
 * @date 2024-07-13
 * 
 * @copyright Copyright (c) 2024
 * 
 * 역시... 원트컷~!
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

#define INF 987654321

using namespace std;

int node_cnt, edge_cnt, burger_cnt, burger_dist, coffee_cnt, coffee_dist;
vector<vector<pair<int, int> > > maps;
vector<int> burgers;
vector<int> coffees;
vector<int> b_visited;
vector<int> c_visited;

void print_burger_dist() {
    for(int cost : b_visited) cout<<cost<<" ";
    cout<<"\n";
}

void print_coffee_dist() {
    for(int cost : c_visited) cout<<cost<<" ";
    cout<<"\n";
}

void burger_dijkstra() {
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
    b_visited.resize(node_cnt + 1, INF);
    for(auto burger : burgers) {
        pq.push(make_pair(0, burger));
        b_visited[burger] = 0;
    }
    while(!pq.empty()) {
        auto[cost, pos] = pq.top(); pq.pop();
        if (b_visited[pos] != cost) continue;
        for(int x=0; x<maps[pos].size(); x++) {
            int npos = maps[pos][x].first;
            int ncost = maps[pos][x].second + cost;
            if (b_visited[npos] <= ncost || ncost > burger_dist) continue;
            pq.push(make_pair(ncost, npos));
            b_visited[npos] = ncost;
        }
    }
}

void coffee_dijkstra() {
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
    c_visited.resize(node_cnt + 1, INF);
    for(auto coffee : coffees) {
        pq.push(make_pair(0, coffee));
        c_visited[coffee] = 0;
    }
    while(!pq.empty()) {
        auto[cost, pos] = pq.top(); pq.pop();
        if (c_visited[pos] != cost) continue;
        for(int x=0; x<maps[pos].size(); x++) {
            int npos = maps[pos][x].first;
            int ncost = maps[pos][x].second + cost;
            if (c_visited[npos] <= ncost || ncost > coffee_dist) continue;
            pq.push(make_pair(ncost, npos));
            c_visited[npos] = ncost;
        }
    }
}



int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>node_cnt>>edge_cnt;
    maps.resize(node_cnt + 1);
    for(int i=0; i<edge_cnt; i++) {
        int node1, node2, cost; cin>>node1>>node2>>cost;
        maps[node1].push_back(make_pair(node2, cost));
        maps[node2].push_back(make_pair(node1, cost));
    }
    cin>>burger_cnt>>burger_dist;
    burgers.resize(burger_cnt);
    for(int i=0; i<burger_cnt; i++) cin>>burgers[i];
    cin>>coffee_cnt>>coffee_dist;
    coffees.resize(coffee_cnt);
    for(int i=0; i<coffee_cnt; i++) cin>>coffees[i];

    burger_dijkstra();
    //print_burger_dist();
    coffee_dijkstra();
    //print_coffee_dist();
    int answer = INF;
    for(int i=1; i<=node_cnt; i++) {
        if (b_visited[i] == INF || b_visited[i] == 0) continue;
        if (c_visited[i] == INF || c_visited[i] == 0) continue;
        answer = min(answer, b_visited[i] + c_visited[i]);
    }
    if (answer == INF) cout<<"-1";
    else cout<<answer;
}