#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct Info {
    int y, x, cnt;
};
int sizeY, sizeX, moveY[4]={0,1,0,-1}, moveX[4]={1,0,-1,0};
vector<vector<bool> > maps;
vector<vector<int> > visited;

bool check_outside(int y, int x) {
    return y < 0 || y >= sizeY || x < 0 || x >= sizeX;
}

void bfs() {
    queue<Info> q;
    q.push({0, 0, 1});
    visited[0][0] = 1;
    while(!q.empty()) {
        auto[y, x, cnt] = q.front(); q.pop();
        for(int d=0; d<4; d++) {
            int ny = y + moveY[d];
            int nx = x + moveX[d];
            int ncnt = cnt + 1;
            if (check_outside(ny, nx) || visited[ny][nx] != 0 || !maps[ny][nx]) continue;
            q.push({ny, nx, ncnt});
            visited[ny][nx] = ncnt;
        }
    }
}

int main() {
    cin>>sizeY>>sizeX;
    maps.resize(sizeY, vector<bool>(sizeX, false));
    visited.resize(sizeX, vector<int>(sizeX, 0));
    for(int y=0; y<sizeY; y++) {
        string row; cin>>row;
        for(int x=0; x<sizeX; x++) {
            maps[y][x] = (row[x] == '1' ? true : false);
        }
    }
    bfs();
    cout<<visited[sizeY-1][sizeX-1];
}