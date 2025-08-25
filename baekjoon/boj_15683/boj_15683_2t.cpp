#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int sizeY, sizeX, moveY[4]={0,1,0,-1}, moveX[4]={1,0,-1,0}, answer = 987654321;
vector<vector<int> > maps;
vector<vector<int> > watching;
vector<pair<int, int> > cameras;
vector<vector<vector<int> > > cam_directions = {
    {},
    {
        {0}, {1}, {2}, {3}
    },
    {
        {0, 2}, {1, 3}
    }, 
    {
        {0, 3}, {3, 2}, {2, 1}, {1, 0}
    },
    {
        {0, 1, 2}, {1, 2, 3}, {0, 2, 3}, {0, 1, 3}
    },
    {
        {0,1,2,3}
    }
};

bool check_outside(int y, int x) {
    return y < 0 || y >= sizeY || x < 0 || x >= sizeX;
}

void watching_boundary(pair<int, int> pos, vector<int>& dirs) {
    auto[sy, sx] = pos;
    watching[sy][sx] += 1;

    for(int d=0; d<dirs.size(); d++) {
        int y = sy, x = sx;        
        while(1) {
            int ny = y + moveY[dirs[d]];
            int nx = x + moveX[dirs[d]];
            if (check_outside(ny, nx) || maps[ny][nx] == 6) break;
            watching[ny][nx] += 1;
            y = ny;
            x = nx;
        }
    }
}

void cancel_watching(pair<int, int> pos, vector<int>& dirs) {
    auto[sy, sx] = pos;
    watching[sy][sx] -= 1;

    for(int d=0; d<dirs.size(); d++) {
        int y = sy, x = sx;        
        while(1) {
            int ny = y + moveY[dirs[d]];
            int nx = x + moveX[dirs[d]];
            if (check_outside(ny, nx) || maps[ny][nx] == 6) break;
            watching[ny][nx] -= 1;
            y = ny;
            x = nx;
        }
    }
}

int count_darkside() {
    int cnt = 0;
    for(int y=0; y<sizeY; y++) {
        for(int x=0; x<sizeX; x++) {
            if (maps[y][x] == 0 && watching[y][x] == 0) cnt++;
        }
    }
    return cnt;
}

void dfs(int idx) {
    if (idx == cameras.size()) {
        answer = min(count_darkside(), answer);
        return ;
    }
    int camera = maps[cameras[idx].first][cameras[idx].second];
    for(int c=0; c<cam_directions[camera].size(); c++) {
        watching_boundary(cameras[idx], cam_directions[camera][c]);
        dfs(idx + 1);
        cancel_watching(cameras[idx], cam_directions[camera][c]);
    }
}

int main() {
    cin>>sizeY>>sizeX;
    maps.resize(sizeY, vector<int>(sizeX, 0));
    watching.resize(sizeY, vector<int>(sizeX, 0));
    for(int y=0; y<sizeY; y++) {
        for(int x=0; x<sizeX; x++) {
            cin>>maps[y][x];
            if (maps[y][x] >= 1 && maps[y][x] <= 5) cameras.push_back({y, x});
        }
    }
    dfs(0);
    cout<<answer;
}