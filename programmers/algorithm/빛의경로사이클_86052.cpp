/**
 * @file 빛의경로사이클_86052.cpp
 * @brief 프로그래머스 lv.2 빛의 경로 사이클
 * @version 0.1
 * @date 2024-08-13
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int moveY[4]={0,1,0,-1}, moveX[4]={1,0,-1,0};
vector<vector<vector<bool> > > visited;

int next_dir(int dir, char symbol) {
    // S
    if (symbol == 'S') return dir;
    
    // L
    else if (symbol == 'L') {
        if (dir == 0) return 3;
        return dir-1;
    }
    // R
    else if (symbol == 'R') {
        if (dir == 3) return 0;
        return dir+1;
    }
}

int dfs(vector<string>& maps, int y, int x, int dir, int len) {
    if (visited[y][x][dir]) return len;
    visited[y][x][dir] = true;
    
    int ndir = next_dir(dir, maps[y][x]);
    int ny = y + moveY[ndir];
    int nx = x + moveX[ndir];
    
    // 범위 밖의 경우에 대해서 조건 처리
    if (ny < 0) ny = maps.size() - 1;
    else if (ny >= maps.size()) ny = 0;
    if (nx < 0) nx = maps[0].size() - 1;
    else if (nx >= maps[0].size()) nx = 0;
    
    return dfs(maps, ny, nx, ndir, len+1);
}

vector<int> solution(vector<string> grid) {
    vector<int> answer;
    visited.resize(grid.size(), vector<vector<bool> >(grid[0].size(), vector<bool>(4, false)));
    for(int y=0; y<grid.size(); y++) {
        for(int x=0; x<grid[y].size(); x++) {
            for(int d=0; d<4; d++) {
                int len = dfs(grid, y, x, d, 0);
                if (len != 0) answer.push_back(len);
            }
        }
    }
    sort(answer.begin(), answer.end());
    return answer;
}