#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int sizeY, sizeX, moveY[4]={0,1,0,-1}, moveX[4]={1,0,-1,0}, jy, jx;
vector<string> maps;
vector<vector<int> > visited;
vector<vector<int> > fire;

bool check_outside(int y, int x) {
    return y < 0 || y >= sizeY || x < 0 || x >= sizeX;
}

void spread_fire(vector<pair<int, int> >& spos) {
    queue<pair<int, int> > q;
    for(auto pos : spos) {
        q.push(pos);
        fire[pos.first][pos.second] = 0;
    }
    while(!q.empty()) {
        auto[y, x] = q.front(); q.pop();
        for(int d=0; d<4; d++) {
            int ny = y + moveY[d];
            int nx = x + moveX[d];
            if (check_outside(ny, nx) || maps[ny][nx] == '#' || fire[ny][nx] != -1) continue;
            q.push({ny, nx});
            fire[ny][nx] = fire[y][x] + 1;
        }
    }
}

int move_jihoon() {
    queue<pair<int, int> > q;
    q.push({jy, jx});
    visited[jy][jx] = 0;
    while(!q.empty()) {
        auto[y, x] = q.front(); q.pop();
        for(int d=0; d<4; d++) {
            int ny = y + moveY[d];
            int nx = x + moveX[d];
            int ncost = visited[y][x] + 1;
            if (check_outside(ny, nx)) {
                return ncost;
            }
            if (maps[ny][nx] == '#' || (fire[ny][nx] != -1 && fire[ny][nx] <= ncost) || visited[ny][nx]!= -1) continue;
            q.push({ny, nx});
            visited[ny][nx] = ncost;
        }
    }
    return -1;
}

int main() {
    cin>>sizeY>>sizeX;
    visited.resize(sizeY, vector<int>(sizeX, -1));
    fire.resize(sizeY, vector<int>(sizeX, -1));
    vector<pair<int, int> > pos;
    for(int y=0; y<sizeY; y++) {
        string row; cin>>row;
        maps.push_back(row);
        for(int x=0; x<maps[y].size(); x++) {
            if (maps[y][x] == 'J') {
                jy = y;
                jx = x;
            }
            else if (maps[y][x] == 'F') {
                pos.push_back({y, x});
            }
        }
    }
    spread_fire(pos);
    int answer = move_jihoon();
    cout<<((answer == -1) ? "IMPOSSIBLE\n" : to_string(answer));
}