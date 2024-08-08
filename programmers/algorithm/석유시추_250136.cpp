/**
 * @file 석유시추_250136.cpp
 * @brief 프로그래머스 lv.2 PCCP 기출문제, 2번 석유 시추
 * @version 0.1
 * @date 2024-08-08
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <string>
#include <vector>
#include <queue>
#include <iostream>
#include <set>

using namespace std;

int moveY[4]={0,1,0,-1}, moveX[4]={1,0,-1,0};
vector<int> groups;
vector<vector<int> > visited;

void print_visited(){
    for(int y=0; y<visited.size(); y++) {
        for(int x=0; x<visited[y].size(); x++) {
            cout<<visited[y][x]<<" ";
        }
        cout<<"\n";
    }
}

bool check_outside(int y, int x) {
    return y < 0 || y >= visited.size() || x < 0 || x >= visited[0].size(); 
}

int bfs(vector<vector<int> >& maps, int sy, int sx, int group_num) {
    int cnt = 1;
    queue<pair<int, int> > q;
    q.push({sy, sx});
    visited[sy][sx] = group_num;
    while(!q.empty()) {
        auto[y, x] = q.front(); q.pop();
        for(int d=0; d<4; d++) {
            int ny = y + moveY[d];
            int nx = x + moveX[d];
            if (check_outside(ny, nx) || visited[ny][nx] > 0 || maps[ny][nx] == 0) continue;
            q.push({ny, nx});
            visited[ny][nx] = group_num;
            cnt++;
        }
    }
    return cnt;
}

int solution(vector<vector<int>> land) {
    int answer = 0;
    int group_num = 1;
    groups.push_back(0); // 1부터 하기 위한 push
    
    visited.resize(land.size(), vector<int>(land[0].size(), 0));
    for(int y=0; y<land.size(); y++) {
        for(int x=0; x<land[y].size(); x++) {
            if (land[y][x] == 1 && visited[y][x] == 0) {
                groups.push_back(bfs(land, y, x, group_num++));
            }
        }
    }
    for(int x=0; x<land[0].size(); x++) {
        set<int> unique_groups;
        int cnt = 0;
        for(int y=0; y<land.size(); y++) {
            unique_groups.insert(visited[y][x]);
        }
        for(auto group : unique_groups) {
            cnt += groups[group];
        }
        answer = max(answer, cnt);
    }
    return answer;
}