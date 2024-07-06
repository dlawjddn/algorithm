/**
 * @file boj_16234.cpp
 * @brief 백준 gold4 인구이동
 * @version 0.1
 * @date 2024-07-07
 * 
 * @copyright Copyright (c) 2024
 * 
 * 2년전에 못 푼 문제 원트 컷~!!
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cmath>

using namespace std;

int sq_size, L, R, moveY[4]={0,1,0,-1}, moveX[4]={1,0,-1,0};
vector<vector<int> > maps;
vector<vector<int> > visited;

bool check_outside(int y, int x) {
    return y < 0 || y >= sq_size || x < 0 || x >= sq_size;
}

pair<int, int> bfs(int group_num, int sy, int sx) {
    int group_size = 1;
    int group_value = maps[sy][sx];
    queue<pair<int, int> > q;
    q.push(make_pair(sy, sx));
    visited[sy][sx] = group_num;
    while(!q.empty()) {
        auto[y, x] = q.front(); q.pop();
        for(int d=0; d<4; d++) {
            int ny = y + moveY[d];
            int nx = x + moveX[d];
            if (check_outside(ny, nx) || L > abs(maps[ny][nx] - maps[y][x]) || abs(maps[ny][nx] - maps[y][x]) > R || visited[ny][nx] != 0) continue;
            q.push(make_pair(ny, nx));
            visited[ny][nx] = group_num;
            group_size++;
            group_value += maps[ny][nx];
        }
    }
    if (group_size == 1) {
        visited[sy][sx] = 0;
    }
    return make_pair(group_size, group_value);
}

void solution() {
    int day = 0;
    while(1) {
        //cout<<day<<"\n";
        visited = vector<vector<int> >(sq_size, vector<int>(sq_size, 0));
        vector<int> groups(2501, 0);
        int group_num = 1;
        for(int y=0; y<sq_size; y++) {
            for(int x=0; x<sq_size; x++) {
                if (visited[y][x] == 0) {
                    pair<int, int> group = bfs(group_num, y, x);
                    if (group.first == 1) continue;
                    else groups[group_num++] = group.second / group.first;
                }
            }
        }
        for(int y=0; y<sq_size; y++) {
            for(int x=0; x<sq_size; x++) {
                if (visited[y][x] == 0) continue;
                else {
                    maps[y][x] = groups[visited[y][x]];
                }
            }
        }
        if (group_num == 1) break;
        day++;
    }
    cout<<day;
}

int main(){
    cin>>sq_size>>L>>R;
    maps.resize(sq_size, vector<int>(sq_size));
    for(int y=0; y<sq_size; y++) {
        for(int x=0; x<sq_size; x++) {
            cin>>maps[y][x];
        }
    }
    solution();
}