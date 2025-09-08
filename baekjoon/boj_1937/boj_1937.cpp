#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int sq_size, moveY[4]={0,1,0,-1}, moveX[4]={1,0,-1,0};
vector<vector<int> > maps;
vector<vector<int> > visited;

bool check_outside(int y, int x) {
    return y < 0 || y >= sq_size || x < 0 || x >= sq_size;
}

int dfs(int y, int x) {
    if (visited[y][x] != 0) return visited[y][x];
    visited[y][x] = 1;
    int cnt = 0;
    for(int d=0; d<4; d++) {
        int ny = y + moveY[d];
        int nx = x + moveX[d];
        if (check_outside(ny, nx) || maps[y][x] >= maps[ny][nx]) continue;
        cnt = max(cnt, dfs(ny, nx));
    }
    return visited[y][x] += cnt;
}

int main() {
    cin>>sq_size;
    maps.resize(sq_size, vector<int>(sq_size, 0));
    visited.resize(sq_size, vector<int>(sq_size, 0));
    for(int y=0; y<sq_size; y++) {
        for(int x=0; x<sq_size; x++) {
            cin>>maps[y][x];
        }
    }
    int answer = 0;
    for(int y=0; y<sq_size; y++) {
        for(int x=0; x<sq_size; x++) {
            answer = max(answer, dfs(y, x));
        }
    }
    cout<<answer;
}