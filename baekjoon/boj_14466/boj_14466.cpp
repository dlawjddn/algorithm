/**
 * @file boj_14466.cpp
 * @brief 백준 gold3 소가 걸어간 이유 6
 * @version 0.1
 * @date 2024-06-27
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int sq_size = 0, cow_cnt = 0, road_cnt = 0, moveY[4]={0,1,0,-1}, moveX[4]={1,0,-1,0};
vector<pair<int, int> > cows;
vector<vector<int> > maps(101, vector<int>(101, 0));
//vector<pair<pair<int, int>, pair<int, int> > > roads;
bool roads[101][101][101][101];

bool check_outside(int y, int x) {
    return y < 1 || y > sq_size || x < 1 || x > sq_size;
}

vector<vector<bool> > bfs(int sy, int sx) {
    vector<vector<bool> > visited(sq_size + 1, vector<bool>(sq_size + 1, false));
    queue<pair<int, int> > q;
    q.push(make_pair(sy, sx));
    visited[sy][sx] = true;
    while(!q.empty()) {
        int y = q.front().first;
        int x = q.front().second; q.pop();
        for(int d=0; d<4; d++) {
            int ny = y + moveY[d];
            int nx = x + moveX[d];
            if (check_outside(ny, nx) || visited[ny][nx] || roads[y][x][ny][nx] || roads[ny][nx][y][x]) continue;
            q.push(make_pair(ny, nx));
            visited[ny][nx] = true;
        }
    }
    return visited;
}

int solution(){
    int answer = 0;
    for(int i=1; i<cow_cnt; i++) {
        vector<vector<bool> > visited = bfs(cows[i].first, cows[i].second);
        for(int j=i+1; j<=cow_cnt; j++) {
            if (!visited[cows[j].first][cows[j].second]) answer++;
        }
    }
    return answer;
}

int main(){
    cin>>sq_size>>cow_cnt>>road_cnt;
    cows.resize(cow_cnt+1);
    for(int i=0; i<road_cnt; i++) {
        int sy, sx, dy, dx;
        cin>>sy>>sx>>dy>>dx;
        roads[sy][sx][dy][dx] = true;
        roads[dy][dx][sy][sx] = true;
        //roads.push_back(make_pair(make_pair(sy, sx), make_pair(dy, dx)));
    }
    for(int i=1; i<=cow_cnt; i++) {
        int cowy, cowx;
        cin>>cowy>>cowx;
        cows[i] = make_pair(cowy, cowx);
    }

    cout<<solution();
    
}