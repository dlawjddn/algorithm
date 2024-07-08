/**
 * @file boj_24464.cpp
 * @brief 백준 gold4 미로
 * @version 0.1
 * @date 2024-07-08
 * 
 * @copyright Copyright (c) 2024
 * 
 * 기존에 나는 그래프 탐색을 진행할 때, 경로를 묻는 문제는 구조체를 만들어서 각 위치마다의 경로를 기억하게 해서 풀었다...
 * 하지만 이 방법은 시간 초과가 발생했고, 현재 위치의 전의 위치를 담아서 경로를 탐색하는 방법이 훨씬 빠르게 작동했다.. ㅠ
 * 왜 시간초과가 나는지는 아직 모르겠당 ㅠ 한 가지 확실한건 이 방법이 훨씬 빠르다는거니까 이 방법을 사용해야겠다..
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int sizeY, sizeX, moveY[4]={0,1,0,-1}, moveX[4]={1,0,-1,0};
vector<string> maps;
vector<string> result;
vector<pair<int, int> > points;
vector<vector<bool> > visited;

bool check_outside(int y, int x) {
    return y < 0 || y >= sizeY || x < 0 || x >= sizeX;
}

vector<pair<int, int> > bfs() {
    queue<pair<int, int> > q;
    vector<vector<pair<int, int> > > before(sizeY, vector<pair<int, int> >(sizeX, make_pair(-1, -1)));
    visited.resize(sizeY, vector<bool>(sizeX, false));
    pair<int, int> start = points[0];
    pair<int, int> end = points[1];

    q.push(start);
    visited[start.first][start.second] = true;
    while(!q.empty()) {
        auto[y, x] = q.front(); q.pop();
        // 종료지점에 도달한 경우
        if (y == end.first && x == end.second) {
            vector<pair<int, int> > path;
            while(y != -1 && x != -1) {
                path.push_back(make_pair(y, x));
                pair<int, int> next = before[y][x];
                y = next.first; x=next.second;
            }
            reverse(path.begin(), path.end());
            return path;
        }
        for(int d=0; d<4; d++) {
            int ny = y + moveY[d];
            int nx = x + moveX[d];
            if (check_outside(ny, nx) || maps[ny][nx] == '+' || visited[ny][nx]) continue;
            q.push(make_pair(ny, nx));
            visited[ny][nx] = true;
            before[ny][nx] = make_pair(y, x);
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>sizeY>>sizeX;
    maps.resize(sizeY);
    result.resize(sizeY);
    for(int y=0; y<sizeY; y++) {
        cin>>maps[y];
        result[y] = maps[y];
        for(int x=0; x<sizeX; x++) {
            if (maps[y][x] == '.' && ((y ==0 || y == sizeY - 1) || (x == 0 || x == sizeX - 1))) {
                points.push_back(make_pair(y, x));
                continue;
            }
            if (maps[y][x] == '.') result[y][x] = '@';
        }
    }
    vector<pair<int, int> > path = bfs();
    for(pair<int, int> p : path) {
        result[p.first][p.second] = '.';
    }
    for(int y=0; y<sizeY; y++) {
        cout<<result[y]<<"\n";
    }
}