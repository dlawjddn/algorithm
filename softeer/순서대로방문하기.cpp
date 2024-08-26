/**
 * @file 순서대로방문하기.cpp
 * @brief HSAT 7회 정기 코딩 인증평가 기출문제 lv.3 순서대로 방문하기
 * @version 0.1
 * @date 2024-08-26
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;

int answer = 0, sq_size = 0, points_cnt = 0, moveY[4]={0,1,0,-1}, moveX[4]={1,0,-1,0};
vector<vector<int> > maps;
vector<vector<bool> > visited;
vector<pair<int, int> > points;

bool check_outside(int y, int x) {
    return y < 0 || y >= sq_size || x < 0 || x >= sq_size;
}

void dfs(int idx, int y, int x) {
    if (idx == points.size()) {
        answer++;
        return ;
    }
    if (y == points[idx].first && x == points[idx].second) { // 다음에 방문해야하는 위치인 경우
        dfs(idx + 1, y, x);
    }
    for(int d=0; d<4; d++) {
        int ny = y + moveY[d];
        int nx = x + moveX[d];
        if (check_outside(ny, nx) || visited[ny][nx] || maps[ny][nx] == 1) continue;
        visited[ny][nx] = true;
        dfs(idx, ny, nx);
        visited[ny][nx] = false;
    }
}

int main(int argc, char** argv){
    cin>>sq_size>>points_cnt;
    maps.resize(sq_size, vector<int>(sq_size, 0));
    visited.resize(sq_size, vector<bool>(sq_size, false));
    points.resize(points_cnt);
    for(int y=0; y<sq_size; y++) {
        for(int x=0; x<sq_size; x++) {
            cin>>maps[y][x];
        }
    }
    for(int i=0; i<points_cnt; i++) {
        cin>>points[i].first>>points[i].second;
        points[i].first -= 1;
        points[i].second -= 1;
    }
    visited[points[0].first][points[0].second] = true;
    dfs(1, points[0].first, points[0].second);
    cout<<answer;
}