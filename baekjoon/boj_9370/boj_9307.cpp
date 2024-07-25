/**
 * @file boj_9307.cpp
 * @brief 백준 gold2 미확인 도착지
 * @version 0.1
 * @date 2024-07-25
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

#define INF 1e9

using namespace std;

int node_cnt, edge_cnt, dest_cnt, start;
vector<int> positions(2);
vector<int> visited_from_start;
vector<int> visited_from_position1;
vector<int> visited_from_position2;
vector<int> destinations;
vector<vector<pair<int, int> > > maps;

void print_visited() {
    cout<<"start\n";
    for(int i=1; i<=node_cnt; i++) cout<<visited_from_start[i]<<" ";
    cout<<"\n";
    cout<<"position1\n";
    for(int i=1; i<=node_cnt; i++) cout<<visited_from_position1[i]<<" ";
    cout<<"\n";
    cout<<"position2\n";
    for(int i=1; i<=node_cnt; i++) cout<<visited_from_position2[i]<<" ";
    cout<<"\n";
}

vector<int> dijkstra(int check) {
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
    vector<int> visited(node_cnt + 1, INF);
    if (check == 0) {
        pq.push(make_pair(0, start));
        visited[start] = 0;
    } else if (check == 1) {
        pq.push(make_pair(0, positions[0]));
        visited[positions[0]] = 0;
    } else {
        pq.push(make_pair(0, positions[1]));
        visited[positions[1]] = 0;
    }
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

int main(){
    int test_case; cin>>test_case;
    for(int i=0; i<test_case; i++) {
        cin>>node_cnt>>edge_cnt>>dest_cnt;
        cin>>start>>positions[0]>>positions[1];
        destinations = vector<int>(dest_cnt);
        maps = vector<vector<pair<int, int> > >(node_cnt + 1);
        for(int j=0; j<edge_cnt; j++) {
            int node1, node2, cost; cin>>node1>>node2>>cost;
            maps[node1].push_back(make_pair(node2, cost));
            maps[node2].push_back(make_pair(node1, cost));
        }
        for(int j=0; j<dest_cnt; j++) cin>>destinations[j];
        visited_from_start = dijkstra(0);
        sort(destinations.begin(), destinations.end());
        visited_from_position1 = dijkstra(1);
        visited_from_position2 = dijkstra(2);
        for(auto destination : destinations) {
            if (visited_from_start[destination] == visited_from_start[positions[1]] + visited_from_position1[positions[1]] + visited_from_position1[destination] ||
                visited_from_start[destination] == visited_from_start[positions[0]] + visited_from_position2[positions[0]] + visited_from_position2[destination])
                cout<<destination<<" ";
        }
        cout<<"\n";
        //print_visited();
    }
}