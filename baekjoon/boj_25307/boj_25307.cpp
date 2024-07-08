/**
 * @file boj_25307.cpp
 * @brief 백준 gold3 시루의 백화점 구경
 * @version 0.1
 * @date 2024-07-08
 * 
 * @copyright Copyright (c) 2024
 * 
 * 제발.. 쉽게 생각하자..
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int sizeY, sizeX, avoid, startY, startX, moveY[4]={0,1,0,-1}, moveX[4]={1,0,-1,0};
vector<vector<int> > maps;
vector<vector<int> > visited;
queue<pair<int, int> > q;

void print_maps(){
    for(int y=0; y<sizeY; y++) {
        for(int x=0; x<sizeX; x++) {
            cout<<maps[y][x]<<" ";
        }
        cout<<"\n";
    }
}

void print_visited(){
    for(int y=0; y<sizeY; y++) {
        for(int x=0; x<sizeX; x++) {
            cout<<visited[y][x]<<" ";
        }
        cout<<"\n";
    }
}

bool check_outside(int y, int x) {
    return y < 0 || y >= sizeY || x < 0 || x >= sizeX;
}

void be_careful() {
    while(!q.empty()) {
        auto[y, x] = q.front(); q.pop();
        if (visited[y][x] == avoid + 1) continue;
        for(int d=0; d<4; d++) {
            int ny = y + moveY[d];
            int nx = x + moveX[d];
            if (check_outside(ny, nx) || visited[ny][nx] != 0) continue;
            q.push(make_pair(ny, nx));
            visited[ny][nx] = visited[y][x] + 1;
            maps[ny][nx] = 1;
        }
    }
}

int bfs() {
    visited = vector<vector<int> >(sizeY, vector<int>(sizeX, 0));
    q.push(make_pair(startY, startX));
    visited[startY][startX] = 1;
    while(!q.empty()) {
        auto[y, x] = q.front(); q.pop();
        if (maps[y][x] == 2) {
            return visited[y][x] - 1;
        }
        for(int d=0; d<4; d++) {
            int ny = y + moveY[d];
            int nx = x + moveX[d];
            if (check_outside(ny, nx) || visited[ny][nx] != 0 || maps[ny][nx] == 1) continue;
            q.push(make_pair(ny, nx));
            visited[ny][nx] = visited[y][x] + 1;
        }
    }
    return -1;
}

int main(){
    cin>>sizeY>>sizeX>>avoid;
    maps.resize(sizeY, vector<int>(sizeX, 0));
    visited.resize(sizeY, vector<int>(sizeX, 0));
    for(int y=0; y<sizeY; y++) {
        for(int x=0; x<sizeX; x++) {
            cin>>maps[y][x];
            if (maps[y][x] == 4) {
                startY = y;
                startX = x;
            }
            else if (maps[y][x] == 3) {
                q.push(make_pair(y, x));
                visited[y][x] = 1;
                maps[y][x] = 1;
            }
        }
    }
    be_careful();
    //print_maps();
    cout<<bfs();
    //print_visited();

}