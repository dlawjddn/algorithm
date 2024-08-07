/**
 * @file 리코쳇로봇_169199.cpp
 * @brief 프로그래머스 lv.2 리코쳇로봇
 * @version 0.1
 * @date 2024-08-07
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <string>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

struct Info {
    int y, x, cnt;
};
int moveY[4]={0,1,0,-1}, moveX[4]={1,0,-1,0};
vector<vector<vector<bool> > > visited;

Info make_info(int y, int x, int cnt) {
    Info info;
    info.y = y;
    info.x = x;
    info.cnt = cnt;
    return info;
}

bool check_outside(int y, int x) {
    return y < 0 || y >= visited.size() || x < 0 || x >= visited[0].size();
}

int bfs(vector<string>& board, int sy, int sx) {
    visited.resize(board.size(), vector<vector<bool> >(board[0].size(), vector<bool>(4, false)));
    queue<Info> q;
    for(int d=0; d<4; d++) {
        q.push(make_info(sy, sx, 0));
        visited[sy][sx][d] = true;
    }
    while(!q.empty()) {
        auto[y, x, cnt] = q.front(); q.pop();
        if (board[y][x] == 'G') return cnt;
        for(int d=0; d<4; d++) {
            int ny = y + moveY[d];
            int nx = x + moveX[d];
            while(!check_outside(ny, nx) && board[ny][nx] != 'D') {
                ny += moveY[d];
                nx += moveX[d];
            }
            ny -= moveY[d];
            nx -= moveX[d];
            if (visited[ny][nx][d]) continue;
            q.push(make_info(ny, nx, cnt + 1));
            visited[ny][nx][d] = true;
        }
    }
    return -1;
}

int solution(vector<string> board) {
    int answer = 0;
    for(int y=0; y<board.size(); y++) {
        for(int x=0; x<board[y].size(); x++) {
            if (board[y][x] == 'R') {
                 return bfs(board, y, x);
            }
        }
    }
}