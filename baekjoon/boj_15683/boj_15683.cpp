/**
 * @file boj_15683.cpp
 * @brief 백준 gold3 감시
 * @version 0.1
 * @date 2024-08-01
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>

#define INF 987654321

using namespace std;

int sizeY, sizeX, empty_cnt = 0, answer = INF, area_cnt = 0, moveY[4]={0,1,0,-1}, moveX[4]={1,0,-1,0};
vector<vector<int> > maps;
vector<vector<int> > watching;
vector<pair<int, int> > cameras;
vector<vector<vector<int> > > cam_direction = {
    {
        {0},
        {1},
        {2},
        {3}
    },
    {
        {0,2},
        {1,3}
    },
    {
        {0,1},
        {1,2},
        {2,3},
        {3,0}
    },
    {
        {0,1,2},
        {0,1,3},
        {0,2,3},
        {1,2,3}
    },
    {
        {0,1,2,3}
    }
};

void print_watching() {
    cout<<"\n";
    for(int y=0; y<sizeY; y++) {
        for(int x=0; x<sizeX; x++) {
            cout<<watching[y][x]<<" ";
        }
        cout<<"\n";
    }
    cout<<"\n";
}

bool check_outside(int y, int x) {
    return y < 0 || y >= sizeY || x < 0 || x >= sizeX;
}

void choose_direction(int camera_num, int way, int sy, int sx) {
    for(int d=0; d<cam_direction[camera_num][way].size(); d++) {
        int dir = cam_direction[camera_num][way][d];
        int y = sy + moveY[dir];
        int x = sx + moveX[dir];
        while(!check_outside(y, x) && maps[y][x] != 6) {
            if (watching[y][x] == 0 && maps[y][x] == 0) area_cnt++;
            watching[y][x] += 1;
            y += moveY[dir];
            x += moveX[dir];
        }
    }
}

void cancel_direction(int camera_num, int way, int sy, int sx) {
    for(int d=0; d<cam_direction[camera_num][way].size(); d++) {
        int dir = cam_direction[camera_num][way][d];
        int y = sy + moveY[dir];
        int x = sx + moveX[dir];
        while(!check_outside(y, x) && maps[y][x] != 6) {
            watching[y][x] -= 1;
            if (watching[y][x] == 0 && maps[y][x] == 0) area_cnt--;
            y += moveY[dir];
            x += moveX[dir];
        }
    }
}

void dfs(int camera_idx) {
    if (camera_idx == cameras.size()) {
        //print_watching();
        //cout<<area_cnt<<"\n";
        answer = min(answer, empty_cnt - area_cnt);
        return ;
    }
    int camera = maps[cameras[camera_idx].first][cameras[camera_idx].second];
    for(int way=0; way<cam_direction[camera-1].size(); way++) {
        int sy = cameras[camera_idx].first;
        int sx = cameras[camera_idx].second;
        choose_direction(camera-1, way, sy, sx);
        dfs(camera_idx + 1);
        cancel_direction(camera-1, way, sy, sx);
    }
}

int main(){
    cin>>sizeY>>sizeX;
    maps.resize(sizeY, vector<int>(sizeX, 0));
    watching.resize(sizeY, vector<int>(sizeX, 0));
    for(int y=0; y<sizeY; y++) {
        for(int x=0; x<sizeX; x++) {
            cin>>maps[y][x];
            if (maps[y][x] >= 1 && maps[y][x] <= 5) {
                cameras.push_back({y, x});
            } else if (maps[y][x] == 0) empty_cnt++;
        }
    }
    dfs(0);
    cout<<answer;
}