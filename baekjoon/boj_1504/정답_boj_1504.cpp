/**
 * @file boj_1504.cpp
 * @brief 백준 gold4 특정한 최단 경로
 * @version 0.1
 * @date 2024-07-04
 * 
 * @copyright Copyright (c) 2024
 * 
 * 이게 왜 틀리지.. -> check_visit 함수에 오타가 있었음.. ㅅㅂ
 * 
 */
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

#define INF 1987654321

using namespace std;

struct Info {
    int pos, cost;
    bool check1, check2;

    bool operator<(Info other) const {
        return cost > other.cost;
    }
};
int node_cnt, road_cnt, check_point1, check_point2;
vector<vector<pair<int, int> > > maps(801);
vector<vector<int> > visited;

void print_visited() {
    for(int y=1; y<=node_cnt; y++) {
        for(int x=0; x<4; x++) {
            cout<<visited[y][x]<<" ";
        }
        cout<<"\n";
    }
}

Info make_info(int pos, int cost, bool check1, bool check2) {
    Info info;
    info.pos = pos;
    info.cost = cost;
    info.check1 = check1;
    info.check2 = check2;
    return info;
}

int check_visit(bool check1, bool check2) {
    if (check1 && check2) return 3;
    else if (!check1 && check2) return 2;
    else if (check1 && !check2) return 1;
    return 0;
}

int dijkstra() {
    priority_queue<Info> pq;
    if (check_point1 == 1) {
        pq.push(make_info(1, 0, true, false));
        visited[1][check_visit(true, false)] = 0;
    }
    else if  (check_point2 == 1) {
        pq.push(make_info(1, 0, false, true));
        visited[1][check_visit(false, true)] = 0;
    }
    else {
        pq.push(make_info(1, 0, false, false));
        visited[1][check_visit(false, false)] = 0;
    }
    while(!pq.empty()) {
        auto[pos, cost, check1, check2] = pq.top(); pq.pop();
        if (visited[pos][check_visit(check1, check2)] != cost) continue;
        for(int x=0; x<maps[pos].size(); x++) {
            int npos = maps[pos][x].first;
            int ncost = cost + maps[pos][x].second;
            bool ncheck1 = check1, ncheck2 = check2;
            if (npos == check_point1) ncheck1 = true;
            if (npos == check_point2) ncheck2 = true;

            if (visited[npos][check_visit(ncheck1, ncheck2)] <= ncost) continue;
            pq.push(make_info(npos, ncost, ncheck1, ncheck2));
            visited[npos][check_visit(ncheck1, ncheck2)] = ncost;
        }
    }
    if (visited[node_cnt][3] >= INF) return -1;
    return visited[node_cnt][3];
}

int main(){
    cin>>node_cnt>>road_cnt;
    maps.resize(node_cnt + 1, vector<pair<int, int> >());
    visited.resize(node_cnt + 1, vector<int>(4, INF));
    for(int i=0; i<road_cnt; i++) {
        int src, dest, cost; cin>>src>>dest>>cost;
        maps[src].push_back(make_pair(dest, cost));
        maps[dest].push_back(make_pair(src, cost));
    }
    cin>>check_point1>>check_point2;
    cout<<dijkstra();
}