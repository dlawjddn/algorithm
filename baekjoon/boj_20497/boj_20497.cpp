/**
 * @file boj_20497.cpp
 * @brief 백준 gold4 Bessie's Revolution
 * @version 0.1
 * @date 2024-07-08
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int sq_size, answer = 0, moveY[4]={0,1,0,-1}, moveX[4]={1,0,-1,0};
vector<string> maps;
vector<pair<int, int> > empty_place;
vector<vector<bool> > visited;

bool check_outside(int y, int x) {
    return y < 0 || y >= sq_size || x < 0 || x >= sq_size;
}

int dfs(int y, int x, int cnt) {
    visited[y][x] = true;
    for(int d=0; d<4; d++) {
        int ny = y + moveY[d];
        int nx = x + moveX[d];
        if (check_outside(ny, nx) || visited[ny][nx] || maps[ny][nx] == '@') continue;
        cnt = max(cnt, dfs(ny, nx, cnt + 1));
    }
    return cnt;
}

void solution() {
    for(auto pos : empty_place) {
        visited = vector<vector<bool> >(sq_size, vector<bool>(sq_size, false));
        visited[pos.first][pos.second] = true;
        //cout<<"pos: "<<pos.first<<" "<<pos.second<<"\n";
        int div = 0;
        for(int d=0; d<4; d++) {
            int y = pos.first + moveY[d];
            int x = pos.second + moveX[d];
            if (check_outside(y, x) || visited[y][x] || maps[y][x] == '@') continue;
            int cnt = dfs(y, x, 1);
            //cout<<cnt<<" ";
            div++;
        }
        //cout<<"\n";
        if (div >= 2) answer++;
    }
}

int main(){
    cin>>sq_size;
    maps.resize(sq_size);
    for(int y=0; y<sq_size; y++) {
        cin>>maps[y];
        for(int x=0; x<sq_size; x++) {
            if (maps[y][x] == '.') empty_place.push_back(make_pair(y, x));
            else if (maps[y][x] == 'S') maps[y][x] = '@';
        }
    }
    solution();
    cout<<answer;
}