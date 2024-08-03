/**
 * @file boj_21922.cpp
 * @brief 백준 gold5 학부 연구생 민상
 * @version 0.1
 * @date 2024-08-04
 * 
 * @copyright Copyright (c) 2024
 * 
 * 구조체와 vector를 사용하면 시간초과가 발생하는 문제.. ㅎㄷㄷ
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>

using namespace std;

struct Info {
    int y, x, dir;
};
int sizeY, sizeX, moveY[4]={0,1,0,-1}, moveX[4]={1,0,-1,0};
int maps[2001][2001];
bool result[2001][2001];
bool visited[2001][2001][4];
//vector<vector<int> > maps;
//vector<vector<bool> > result;
//vector<vector<vector<bool> > > visited;
vector<pair<int, int> > airconditioner;

void print_result() {
    for(int y=0; y<sizeY; y++) {
        for(int x=0; x<sizeX; x++) {
            cout<<result[y][x]<<" ";
        }
        cout<<"\n";
    }
    cout<<"\n";
}

Info make_info(int y, int x, int dir) {
    Info info;
    info.y = y;
    info.x = x;
    info.dir = dir;
    return info;
}

bool check_outside(int y, int x) {
    return y < 0 || y >= sizeY || x < 0 || x>= sizeX;
}

int next_dir(int symbol, int d) {
    if (symbol == 1) {
        if (d == 0) return 2;
        else if (d== 2) return 0;
        else return d;
    }
    else if (symbol == 2) {
        if (d == 1) return 3;
        else if (d == 3) return 1;
        else return d;
    }
    else if (symbol == 3) { 
        if (d == 0) return 3;
        else if (d == 1) return 2;
        else if (d == 2) return 1;
        else return 0;
    }
    else if (symbol == 4) {
        if (d == 0) return 1;
        else if (d == 1) return 0;
        else if (d == 2) return 3;
        else return 2;
    }
    else return d;
}

int bfs() {
    int cnt = 0;
    queue<pair<pair<int, int>, int> > q;
    for(auto pos : airconditioner) {
        for(int d=0; d<4; d++) {
            q.push({{pos.first, pos.second}, d});
            visited[pos.first][pos.second][d] = true;
        }
        result[pos.first][pos.second] = true;
        cnt++;
    }
    while(!q.empty()) {
        auto[pos, dir] = q.front(); q.pop();
        auto[y, x] = pos;
        int ny = y + moveY[dir];
        int nx = x + moveX[dir];
        if (check_outside(ny, nx) || maps[ny][nx] == 9) continue;
        int ndir = next_dir(maps[ny][nx], dir);
        if (visited[ny][nx][ndir]) continue;
        q.push({{ny, nx}, ndir});
        visited[ny][nx][ndir] = true;
        if (!result[ny][nx]) {
            result[ny][nx] = true;
            cnt++;
        }
    }
    //print_result();
    return cnt;
}

int main(){
    cin>>sizeY>>sizeX;
    memset(result, false, sizeof(result));
    memset(visited, false, sizeof(visited));
    //maps.resize(sizeY, vector<int>(sizeX, 0));
    //result.resize(sizeY, vector<bool>(sizeX, false));
    //visited.resize(sizeY, vector<vector<bool> >(sizeX, vector<bool>(4, false)));
    for(int y=0; y<sizeY; y++) {
        for(int x=0; x<sizeX; x++) {
            cin>>maps[y][x];
            if (maps[y][x] == 9) airconditioner.push_back({y, x});
        }
    }
    cout<<bfs();
}