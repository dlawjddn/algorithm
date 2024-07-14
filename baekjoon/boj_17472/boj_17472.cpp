/**
 * @file boj_17472.cpp
 * @brief 백준 gold1 다리 만들기 2
 * @version 0.1
 * @date 2024-07-14
 * 
 * @copyright Copyright (c) 2024
 * 
 * 상당히 재밌었던 문제 굿!
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>

using namespace std;

int sizeY, sizeX, moveY[4]={0,1,0,-1}, moveX[4]={1,0,-1,0};
vector<int> parents;
vector<vector<int> > maps;
vector<vector<bool> > visited;
vector<vector<pair<int, int> > > groups;
vector<vector<pair<int, int> > > edges;
priority_queue<pair<int, pair<int, int> >, vector<pair<int, pair<int, int> > >, greater<pair<int, pair<int, int> > > > pq;

void print_groups() {
    for(int y=0; y<groups.size(); y++) {
        cout<<"group"<<y<<": \n";
        for(int x=0; x<groups[y].size(); x++) {
            cout<<"("<<groups[y][x].first<<", "<<groups[y][x].second<<") ";
        }
        cout<<"\n";
    }
}

void print_maps() {
    for(int y=0; y<sizeY; y++) {
        for(int x=0; x<sizeX; x++) {
            cout<<maps[y][x]<<" ";
        }
        cout<<"\n";
    }
}

void print_edges() {
    for(int i=0; i<edges.size(); i++) {
        cout<<"node"<<i<<"\n";
        for(int j=0; j<edges[i].size(); j++) {
            cout<<"("<<edges[i][j].first<<", "<<edges[i][j].second<<") ";
        }
        cout<<"\n";
    }
}

int find_parent(int node) {
    if (node == parents[node]) return node;
    return parents[node] = find_parent(parents[node]);
}

void make_union(int parent, int child) {
    parent = find_parent(parent);
    child = find_parent(child);
    parents[child] = parent;
}

bool is_same_parent(int node1, int node2) {
    int n1p = find_parent(node1);
    int n2p = find_parent(node2);
    if (n1p == n2p) return true;
    return false;
}

bool check_outside(int y, int x) {
    return y < 0 || y >= sizeY || x < 0 || x >= sizeX;
}

vector<pair<int, int> > bfs(int sy, int sx, int group_num) {
    vector<pair<int, int> > members;
    queue<pair<int, int> > q;
    q.push(make_pair(sy, sx));
    visited[sy][sx] = true;
    while(!q.empty()) {
        auto[y, x] = q.front(); q.pop();
        members.push_back(make_pair(y, x));
        maps[y][x] = group_num;
        for(int d=0; d<4; d++) {
            int ny = y + moveY[d];
            int nx = x + moveX[d];
            if (check_outside(ny, nx) || maps[ny][nx] == -1 || visited[ny][nx]) continue;
            q.push(make_pair(ny, nx));
            visited[ny][nx] = true;
        }
    }
    return members;
}

void make_group() {
    int group_num = 0;
    for(int y=0; y<sizeY; y++) {
        for(int x=0; x<sizeX; x++) {
            if (maps[y][x] == 1 && !visited[y][x]) {
                groups.push_back(bfs(y, x, group_num));
                group_num++;
            }
        }
    }
}

void build_edge(int sy, int sx, int dir, int start_group) {
    int y = sy, x = sx, len = 0;
    bool fail = false;
    while(maps[y][x] == -1) {
        y += moveY[dir];
        x += moveX[dir];
        if (check_outside(y, x)) {
            fail = true;
            break;
        }
        len++;
    }
    if (fail || len <= 1) return ;
    else {
        edges[start_group].push_back(make_pair(maps[y][x], len));
        pq.push(make_pair(len, make_pair(start_group, maps[y][x])));
    }
}

void make_edge() {
    edges.resize(groups.size());
    for(int i=0; i<groups.size(); i++) {
        for(int j=0; j<groups[i].size(); j++) {
            auto[y, x] = groups[i][j];
            int start_group = i;
            for(int d=0; d<4; d++) {
                int ny = y + moveY[d];
                int nx = x + moveX[d];
                if (check_outside(ny, nx) || maps[ny][nx] != -1) continue;
                build_edge(ny, nx, d, start_group);
            }
        }
    }
}

int kruskal() {
    // 유니온 파인드 기초 세팅
    parents.resize(groups.size());
    for(int i=0; i<groups.size(); i++) parents[i] = i;
    int total_cost = 0, select_cnt = 0;
    // mst 찾기
    while(!pq.empty()) {
        auto[cost, pos] = pq.top(); pq.pop();
        if (is_same_parent(min(pos.first, pos.second), max(pos.first, pos.second))) continue;
        make_union(min(pos.first, pos.second), max(pos.first, pos.second));
        total_cost += cost;
        select_cnt++;
    }
    if (total_cost == 0 || select_cnt != groups.size() - 1) return -1;
    return total_cost;
}

int main(){
    cin>>sizeY>>sizeX;
    maps.resize(sizeY, vector<int>(sizeX));
    visited.resize(sizeY, vector<bool>(sizeX, false));
    for(int y=0; y<sizeY; y++) {
        for(int x=0; x<sizeX; x++) {
            cin>>maps[y][x];
            if (maps[y][x] == 0) maps[y][x] = -1;
        }
    }
    make_group();
    make_edge();
    cout<<kruskal();
}