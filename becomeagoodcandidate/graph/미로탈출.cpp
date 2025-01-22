#include <string>
#include <vector>
#include <queue>

using namespace std;

struct Info {
    int y, x, cost;
};
int sizeY, sizeX, moveY[4]={0,1,0,-1}, moveX[4]={1,0,-1,0};
pair<int, int> start;
pair<int, int> lever;
pair<int, int> out;

bool check_outside(int y, int x) {
    return y < 0 || y >= sizeY || x < 0 || x >= sizeX;
}

int find_route(vector<string>& maps, int sy, int sx, int dy, int dx) {
    queue<Info> q;
    vector<vector<bool> > visited(sizeY, vector<bool>(sizeX, false));
    q.push({sy, sx, 0});
    visited[sy][sx] = true;
    while(!q.empty()) {
        auto[y, x, cost] = q.front(); q.pop();
        if (y == dy && x == dx) return cost;
        for(int d=0; d<4; d++) {
            int ny = y + moveY[d];
            int nx = x + moveX[d];
            if (check_outside(ny, nx) || maps[ny][nx] == 'X' || visited[ny][nx]) continue;
            q.push({ny, nx, cost + 1});
            visited[ny][nx] = true;
        }
    }
    return -1;
}

int solution(vector<string> maps) {
    int answer = 0;
    sizeY = maps.size(), sizeX = maps[0].size();
    for(int y=0; y<maps.size(); y++) {
        for(int x=0; x<maps[y].size(); x++) {
            if (maps[y][x] == 'S') start = {y, x};
            else if (maps[y][x] == 'L') lever = {y, x};
            else if (maps[y][x] == 'E') out = {y, x};
        }
    }
    int to_lever = find_route(maps, start.first, start.second, lever.first, lever.second);
    int to_exit = find_route(maps, lever.first, lever.second, out.first, out.second);
    if (to_lever == -1 || to_exit == -1) return -1;
    return to_lever + to_exit;
}