#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cmath>

#define INF 1987654321

using namespace std;

int sizeY, sizeX, player_cnt, moveY[4]={0,1,0,-1}, moveX[4]={1,0,-1,0};
vector<bool> check;
vector<int> move_size;
vector<vector<int> > maps;
vector<vector<int> > visited;
queue<pair<int, int> > q;

void print_visited() {
    for(int y=0; y<sizeY; y++) {
        for(int x=0; x<sizeX; x++) {
            cout<<visited[y][x]<<" ";
        }
        cout<<"\n";
    }
    cout<<"\n";
}

void print_map() {
    for(int y=0; y<sizeY; y++) {
        for(int x=0; x<sizeX; x++) {
            cout<<maps[y][x]<<" ";
        }
        cout<<"\n";
    }
    cout<<"\n";
}

void find_answer() {
    vector<int> answer(player_cnt + 1, 0);
    for(int y=0; y<sizeY; y++) {
        for(int x=0; x<sizeX; x++) {
            if (maps[y][x] <= 0) continue;
            answer[maps[y][x]]++;
        }
    }
    for(int i=1; i<=player_cnt; i++) cout<<answer[i]<<" ";
    cout<<"\n";
}

bool check_outside(int y, int x) {
    return y < 0 || y >= sizeY || x < 0 || x >= sizeX;
}

void dfs(int player, int y, int x, int depth, int start_cost) {
    if (depth >= move_size[player]) return;
    for(int d=0; d<4; d++) {
        int ny = y + moveY[d];
        int nx = x + moveX[d];
        if (check_outside(ny, nx) || maps[ny][nx] == -1) continue;
        if (visited[ny][nx] <= start_cost + 1) {
            if (visited[ny][nx] < start_cost + 1) continue;
            if (visited[ny][nx] == start_cost + 1 && maps[ny][nx] != maps[y][x]) continue;
        }
        //cout<<"check?\n";
        check[player] = true;
        maps[ny][nx] = player;
        visited[ny][nx] = start_cost + 1;
        dfs(player, ny, nx, depth + 1, start_cost);
    }
}

bool can_move_more() {
    for(int i=1; i<=player_cnt; i++) {
        if (check[i]) return true;
    }
    return false;
}

void move_person() {
    int step = 0;
    while(1) {
        check = vector<bool>(player_cnt + 1, false);
        for(int p=1; p<=player_cnt; p++) {
            for(int y=0; y<sizeY; y++) {
                for(int x=0; x<sizeX; x++) {
                    // 움직일 플레이어 && 지금 움직여야 하는 단계인 경우
                    if (maps[y][x] == p && visited[y][x] == step) dfs(p, y, x, 0, step);
                }
            }
        }
        //print_map();
        //print_visited();
        if (can_move_more()) step++;
        else break;
    }
    find_answer();
}

int main() {
    cin>>sizeY>>sizeX>>player_cnt;
    maps.resize(sizeY, vector<int>(sizeX, 0));
    move_size.resize(player_cnt + 1, 0);
    visited.resize(sizeY, vector<int>(sizeX, INF));
    for(int i=1; i<=player_cnt; i++) cin>>move_size[i];
    for(int y=0; y<sizeY; y++) {
        string s; cin>>s;
        for(int x=0; x<sizeX; x++) {
            if (s[x] >= '1' && s[x] <= '9') {
                int player = s[x] - '0';
                maps[y][x] = player;
                visited[y][x] = 0;
            }
            else if (s[x] == '.') maps[y][x] = 0;
            else maps[y][x] = -1;
        }
    }
    move_person();
    //print_map();
}