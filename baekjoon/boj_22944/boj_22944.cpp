/**
 * @file boj_22944.cpp
 * @brief 백준 gold3 죽음의 비
 * @version 0.1
 * @date 2024-07-31
 * 
 * @copyright Copyright (c) 2024
 * 
 * 그래프 빡구현 오랜만이라 좀 헤맸지만 그래도 나름 잘 풀어낸 듯!
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <numeric>

#define INF 987654321

using namespace std;

struct Info {
    int y, x, hp, shield, cnt;
};
int sq_size, health, umbrella, umbrella_cnt, sy, sx, dy, dx, moveY[4]={0,1,0,-1}, moveX[4]={1,0,-1,0};
vector<string> maps;
vector<vector<vector<int> > > visited;

Info make_info(int y, int x, int hp, int shield, int cnt) {
    Info info;
    info.y = y;
    info.x = x;
    info.hp = hp;
    info.shield = shield;
    info.cnt = cnt;
    return info;
}

bool check_outside(int y, int x) {
    return y < 0 || y >= sq_size || x < 0 || x >= sq_size;
}

int bfs() {
    queue<Info> q;
    visited.resize(sq_size, vector<vector<int> >(sq_size, vector<int>(umbrella_cnt + 1, INF)));
    q.push(make_info(sy, sx, health, 0, 0));
    visited[sy][sx][0] = 0;
    while(!q.empty()) {
        auto[y, x, hp, shield, cnt] = q.front(); q.pop();
        for(int d=0; d<4; d++) {
            int ny = y + moveY[d];
            int nx = x + moveX[d];
            int nhp = hp;
            int nshield = shield;
            int ncnt = cnt;
            if (check_outside(ny, nx)) continue;
            if (maps[ny][nx] == 'U') {
                nshield = umbrella - 1;
                ncnt++;
            }
            else if (maps[ny][nx] == '.') {
                if (nshield > 0) nshield--;
                else  {
                    nhp--;
                    if (nhp == 0) continue;
                }
            }
            if (visited[ny][nx][ncnt] != INF) continue;
            q.push(make_info(ny, nx, nhp, nshield, ncnt));
            visited[ny][nx][ncnt] = visited[y][x][cnt] + 1;
        }
    }
    int result = *min_element(visited[dy][dx].begin(), visited[dy][dx].end());
    return (result == INF) ? -1 : result;
}


int main(){
    cin>>sq_size>>health>>umbrella;
    maps.resize(sq_size);
    for(int y=0; y<sq_size; y++) {
        cin>>maps[y];
        for(int x=0; x<maps[y].size(); x++) {
            if (maps[y][x] == 'S') {
                sy = y;
                sx = x;
            }
            else if (maps[y][x] == 'U') umbrella_cnt++;
            else if (maps[y][x] == 'E') {
                dy = y;
                dx = x;
            }
        }
    }
    cout<<bfs();
}