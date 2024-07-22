/**
 * @file boj_3190.cpp
 * @brief 백준 gold4 뱀
 * @version 0.1
 * @date 2024-07-22
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cmath>

using namespace std;

struct Info {
    int y, x, dir, len, times;
};
int sq_size, apple_cnt, order_cnt, moveY[4]={0,1,0,-1}, moveX[4]={1,0,-1,0};
vector<vector<bool> > apples;
vector<vector<int> > paths;
vector<pair<int, char> > orders;

void print_path() {
    for(int y=0; y<sq_size; y++) {
        for(int x=0; x<sq_size; x++) {
            cout<<paths[y][x]<<" ";
        }
        cout<<"\n";
    }
    cout<<"\n\n";
}

Info make_info(int y, int x, int dir, int len, int times) {
    Info info;
    info.y = y;
    info.x = x;
    info.dir = dir;
    info.len = len;
    info.times = times;
    return info;
}

bool check_outside(int y, int x) {
    return y < 0 || y >= sq_size || x < 0 || x >= sq_size;
}

bool check_mybody(int y, int x, int ny, int nx, int len) {
    if (paths[ny][nx] == -1) return false;
    else {
        if (abs(paths[y][x] - paths[ny][nx]) >= len) return false;
    }
    return true;
}

int bfs() {
    queue<Info> q;
    q.push(make_info(0, 0, 0, 1, 0));
    paths[0][0] = 0;
    while(!q.empty()) {
        auto[y, x, dir, len, time] = q.front(); q.pop();
        // cout<<"time: "<<time<<"\n";
        // cout<<"len: "<<len<<"\n";
        // print_path();
        
        // 몸길이를 늘려, 머리를 다음 칸에 위치 시킨다.
        int ny = y + moveY[dir];
        int nx = x + moveX[dir];
        int ndir = dir;
        int nlen = len;
        int ntime = time + 1;

        // 이동 방향을 변경해야 하는 경우인지 확인
        if (orders[0].first == ntime) {
            if (orders[0].second == 'D') ndir = (ndir + 1) % 4;
            else ndir = (ndir + 3) % 4;
            orders.erase(orders.begin());
        }
        
        // 벽이나 자기 자신과 부딪히면 게임이 끝난다. 
        if (check_outside(ny, nx) || check_mybody(y, x, ny, nx, len)) return ntime;
        
        // 사과 확인
        if (apples[ny][nx]) {
            nlen++;
            apples[ny][nx] = false;
        }
        
        q.push(make_info(ny, nx, ndir, nlen, ntime));
        paths[ny][nx] = ntime;
    }

}

int main(){
    cin>>sq_size>>apple_cnt;
    paths.resize(sq_size, vector<int>(sq_size, -1));
    apples.resize(sq_size, vector<bool>(sq_size, false));
    for(int i=0; i<apple_cnt; i++) {
        int y, x; cin>>y>>x;
        apples[y-1][x-1] = true;
    }
    cin>>order_cnt;
    for(int i=0; i<order_cnt; i++) {
        int times; char dir; cin>>times>>dir;
        orders.push_back(make_pair(times, dir));
    }
    cout<<bfs()<<"\n";
}