#include <iostream>
#include <vector>
#include <queue>
#include <set>

using namespace std;

int sizeY, sizeX, avoid, startY, startX, moveY[4]={0,1,0,-1}, moveX[4]={1,0,-1,0};
vector<vector<int> > maps;
vector<vector<int> > visited;
vector<pair<int, int> > dolls;

void print_maps() {
    for(int y = 0; y < sizeY; y++) {
        for(int x = 0; x < sizeX; x++) {
            cout << maps[y][x] << " ";
        }
        cout << "\n";
    }
}

bool check_outside(int y, int x) {
    return y < 0 || y >= sizeY || x < 0 || x >= sizeX;
}

void avoid_from_dolls() {
    set<pair<int, int> > next_dolls(dolls.begin(), dolls.end());
    for(int i = 0; i < avoid; i++) {
        set<pair<int, int> > current_dolls = next_dolls;
        next_dolls.clear();
        for(auto doll : current_dolls) {
            for(int d = 0; d < 4; d++) {
                int ny = doll.first + moveY[d];
                int nx = doll.second + moveX[d];
                if (check_outside(ny, nx) || maps[ny][nx] == 9) continue;
                next_dolls.insert(make_pair(ny, nx));
                maps[ny][nx] = 9;
            }
        }
    }
}

int bfs() {
    queue<pair<int, int> > q;
    q.push(make_pair(startY, startX));
    visited[startY][startX] = 1;
    while(!q.empty()) {
        auto[y, x] = q.front(); q.pop();
        if (maps[y][x] == 2) {
            return visited[y][x] - 1;
        }
        for (int d = 0; d < 4; d++) {
            int ny = y + moveY[d];
            int nx = x + moveX[d];
            if (check_outside(ny, nx) || visited[ny][nx] != 0 || maps[ny][nx] == 1 || maps[ny][nx] == 3 || maps[ny][nx] == 9) continue;
            q.push(make_pair(ny, nx));
            visited[ny][nx] = visited[y][x] + 1;
        }
    }
    return -1;
}

int main() {
    cin >> sizeY >> sizeX >> avoid;
    maps.resize(sizeY, vector<int>(sizeX, 0));
    visited.resize(sizeY, vector<int>(sizeX, 0));
    bool no_chair = true;
    for(int y = 0; y < sizeY; y++) {
        for(int x = 0; x < sizeX; x++) {
            cin >> maps[y][x];
            if (maps[y][x] == 2) no_chair = false;
            else if (maps[y][x] == 3) dolls.push_back(make_pair(y, x));
            else if (maps[y][x] == 4) {
                startY = y;
                startX = x;
            }
        }
    }
    if (no_chair) {
        cout << -1;
        return 0;
    }
    avoid_from_dolls();
    cout << bfs();
}
