#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int sizeY, sizeX, moveY[4]={0,1,0,-1}, moveX[4]={1,0,-1,0};

bool check_outside(int y, int x) {
    return y < 0 || y >= sizeY || x < 0 || x >= sizeX;
}

int bfs(vector<vector<int> >& maps) {
    queue<pair<int, int> > q;
    vector<vector<int> > visited(sizeY, vector<int>(sizeX, -1));
    q.push({0, 0});
    visited[0][0] = 1;
    while(!q.empty()) {
        auto[y, x] = q.front(); q.pop();
        for(int d=0; d<4; d++) {
            int ny = y + moveY[d];
            int nx = x + moveX[d];
            if (check_outside(ny, nx) || maps[ny][nx] == 0 || visited[ny][nx] >= 0) continue;
            q.push({ny, nx});
            visited[ny][nx] = visited[y][x] + 1;
        }
    }
    return visited[sizeY-1][sizeX-1];
}

int solution(vector<vector<int> > maps){
    sizeY = maps.size(), sizeX = maps[0].size();
    return bfs(maps);
}