#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct Info {
    int y, x, dir;
};
int answer = 0, sizeY, sizeX, moveY[4]={-1, 0, 1, 0}, moveX[4]={0, 1, 0, -1};
vector<vector<int> > maps;
vector<vector<bool> > visited;

int next_dir(int dir) {
    return dir == 0 ? 3 : dir - 1;
}

void move(int sy, int sx, int sdir) {
    queue<Info> q;
    q.push({sy, sx, sdir});
    visited[sy][sx] = true;
    answer += 1;

    while(!q.empty()) {
        auto[y, x, dir] = q.front(); q.pop();
        bool success = false;
        for(int i=0; i<4; i++) {
            int ndir = next_dir(dir);
            int ny = y + moveY[ndir];
            int nx = x + moveX[ndir];
            // 방문했던 곳 or 바다인 경우 -> 다음 방향 조회해야함
            if (visited[ny][nx] || maps[ny][nx] == 1) {
                dir = ndir;
                continue;
            }
            // 방문할 수 있는 곳인 경우
            q.push({ny, nx, ndir});
            visited[ny][nx] = true;
            answer += 1;
            success = true;
            break;
        }
        // 4방향을 모두 조회했는데 갈 수 없는 경우
        if (!success) {
            int ny = y - moveY[dir];
            int nx = x - moveX[dir];
            if (maps[ny][nx] == 1) break;
            q.push({ny, nx, dir});
        }
    }
}

int main() {
    cin>>sizeY>>sizeX;
    maps.resize(sizeY, vector<int>(sizeX, 0));
    visited.resize(sizeX, vector<bool>(sizeX, false));
    int posY, posX, dir; cin>>posY>>posX>>dir;
    for(int y=0; y<sizeY; y++) {
        for(int x=0; x<sizeX; x++) {
            cin>>maps[y][x];
        }
    }
    move(posY, posX, dir);
    cout<<answer;

}