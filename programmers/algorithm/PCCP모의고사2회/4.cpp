/**
 * @file 4.cpp
 * @brief PCCP 모의고사 2회 4번
 * @version 0.1
 * @date 2024-08-31
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Info {
    int y, x, use;
};
int moveY[4] = {0,1,0,-1}, moveX[4]={1,0,-1,0};
vector<vector<bool> > holes;
vector<vector<vector<int> > > visited;

void print_holes() {
    for(int y=0; y<holes.size(); y++) {
        for(int x=0; x<holes[y].size(); x++) {
            cout<<(holes[y][x] ? 1 : 0)<<" ";
        }
        cout<<"\n";
    }
}

Info make_info(int y, int x, int use) {
    Info info;
    info.y = y;
    info.x = x;
    info.use = use;
    return info;
}

bool check_outside(int y, int x) {
    return y < 0 || y >= holes.size() || x < 0 || x >= holes[y].size();  
}

void bfs() {
    queue<Info> q;
    q.push(make_info(0, 0, 0));
    visited[0][0][0] = 1;
    while(!q.empty()) {
        auto[y, x, use] = q.front(); q.pop();
        // 1칸 움직이는거
        for(int d=0; d<4; d++) {
            int ny = y + moveY[d];
            int nx = x + moveX[d];
            int nuse = use;
            if (check_outside(ny, nx) || holes[ny][nx] || visited[ny][nx][nuse] != 0) continue;
            q.push(make_info(ny, nx, nuse));
            visited[ny][nx][nuse] = visited[y][x][use] + 1;
        }
        // 신비로운 신발 사용
        if (use != 0) continue; // 이미 사용한 경우라면 제외
        for(int d=0; d<4; d++) {
            int ny = y + moveY[d] + moveY[d];
            int nx = x + moveX[d] + moveX[d];
            int nuse = 1;
            if (check_outside(ny, nx) || holes[ny][nx] || visited[ny][nx][nuse] != 0) continue;
            q.push(make_info(ny, nx, nuse));
            visited[ny][nx][nuse] = visited[y][x][use] + 1;
        }
    }
}

int solution(int n, int m, vector<vector<int>> hole) {
    int answer = 0;
    holes.resize(m, vector<bool>(n, false));
    visited.resize(m, vector<vector<int> >(n, vector<int>(2, 0)));
    for(auto h : hole) {
        int x = h[0] - 1;
        int y = m + 1 - h[1] - 1;
        holes[m - 1 - y][x] = true;
    }
    bfs();
    if (visited[m-1][n-1][0] == 0 && visited[m-1][n-1][1] == 0) return -1;
    else if (visited[m-1][n-1][0] == 0 || visited[m-1][n-1][1] == 0) return max(visited[m-1][n-1][0] - 1, visited[m-1][n-1][1] - 1);
    else return min(visited[m-1][n-1][0] - 1, visited[m-1][n-1][1] - 1);
}