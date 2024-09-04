/**
 * @file 무인도여행_154540.cpp
 * @brief 프로그래머스 lv2 무인도 여행
 * @version 0.1
 * @date 2024-06-19
 * 
 * @copyright Copyright (c) 2024
 * 
 * dfs return int 에서 어떻게 해야하는지 알게 됐던 문제
 */
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int moveY[4]={0,1,0,-1}, moveX[4]={1,0,-1,0};
vector<vector<bool> > visited(100, vector<bool>(100, false));

void print_visited(vector<string> maps){
    for(int y=0; y<maps.size(); y++){
        for(int x=0; x<maps[y].size(); x++){
            cout<<visited[y][x]<<" ";
        }
        cout<<"\n";
    }
}

bool check_outside(int y, int x, int sizeY, int sizeX) {
    return y < 0 || y >= sizeY || x < 0 || x >= sizeX;
}

int dfs(int y, int x, int num, vector<string> maps) {
    visited[y][x] = true;
    for(int d=0; d<4; d++){
        int ny = y + moveY[d];
        int nx = x + moveX[d];
        if (check_outside(ny, nx, maps.size(), maps[ny].size()) || maps[ny][nx] == 'X' || visited[ny][nx]) continue;
        num += dfs(ny, nx, maps[ny][nx] - '0', maps);
        
    }
    return num;
}

vector<int> solution(vector<string> maps) {
    vector<int> answer;
    for(int i=0; i<maps.size(); i++){
        for(int j=0; j<maps[i].size(); j++){
            if (maps[i][j] == 'X' || visited[i][j]) continue;
            answer.push_back(dfs(i, j, maps[i][j] - '0', maps));
            //print_visited(maps);
        }
    }
    //cout<<answer.size()<<"\n";
    if (answer.size() == 0)
        answer.push_back(-1);
    else
        sort(answer.begin(), answer.end());
    return answer;
}
/**
 * @file 무인도여행_154540.cpp
 * @brief 프로그래머스 lv.2 무인도 여행
 * @version 0.1
 * @date 2024-09-05
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int moveY[4]={0,1,0,-1}, moveX[4]={1,0,-1,0};
vector<vector<bool> > visited;

bool check_outside(int y, int x) {
    return y < 0 || y >= visited.size() || x < 0 || x >= visited[y].size();
}

int bfs(int sy, int sx, vector<string>& maps) {
    int cnt = maps[sy][sx] - '0';
    queue<pair<int, int> > q;
    q.push({sy, sx});
    visited[sy][sx] = true;
    while(!q.empty()) {
        auto[y, x] = q.front(); q.pop();
        for(int d=0; d<4; d++) {
            int ny = y + moveY[d];
            int nx = x + moveX[d];
            if (check_outside(ny, nx) || visited[ny][nx] || maps[ny][nx] == 'X') continue;
            q.push({ny, nx});
            visited[ny][nx] = true;
            cnt += maps[ny][nx] - '0';
        }
    }
    return cnt;
}

vector<int> solve(vector<string>& maps) {
    vector<int> result;
    for(int y=0; y<maps.size(); y++) {
        for(int x=0; x<maps[y].size(); x++) {
            if (visited[y][x] || maps[y][x] == 'X') continue;
            result.push_back(bfs(y, x, maps));
        }
    }
    if (result.empty()) return {-1};
    sort(result.begin(), result.end());
    return result;
}

vector<int> solution(vector<string> maps) {
    visited.resize(maps.size(), vector<bool>(maps[0].size(), false));
    return solve(maps);
}