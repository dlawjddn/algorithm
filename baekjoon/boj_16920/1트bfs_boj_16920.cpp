#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cmath>

#define INF 1987654321

using namespace std;

int sizeY, sizeX, player_cnt, moveY[4]={0,1,0,-1}, moveX[4]={1,0,-1,0};
vector<int> move_size;
vector<vector<pair<int, int> > > players;
vector<string> maps;
vector<vector<int> > result;
vector<vector<int> > visited;
queue<pair<int, int> > q;

// 초기 플레이어의 땅이 여러개 일 수 있음, 장애물 처리 해야함

void print_result() {
    for(int y=0; y<sizeY; y++) {
        for(int x=0; x<sizeX; x++) {
            cout<<result[y][x]<<" ";
        }
        cout<<"\n";
    }
    cout<<"\n";
}

void find_answer() {
    vector<int> answer(player_cnt + 1, 0);
    for(int y=0; y<sizeY; y++) {
        for(int x=0; x<sizeX; x++) {
            if (result[y][x] >= 1 && result[y][x] <= player_cnt) {
                answer[result[y][x]]++;
            }
        }
    }
    for(int i=1; i<=player_cnt; i++) cout<<answer[i]<<" ";
}

bool check_outside(int y, int x) {
    return y < 0 ||  y >= sizeY || x < 0 || x >= sizeX;
}

void get_next_position(int sy, int sx) {
    int player = result[sy][sx];
    int start_cost = visited[sy][sx];
    int move = move_size[player];
    queue<pair<int, int> > temp_q;
    // 1 방향만큼 이동
    for(int d=0; d<4; d++) {
        int ny = sy + moveY[d];
        int nx = sx + moveX[d];
        if (check_outside(ny, nx) || maps[ny][nx] == '#') continue;
        if (result[ny][nx] == 0 || result[ny][nx] == player) {
            if (visited[ny][nx] <= start_cost + 1) {
                if (visited[ny][nx] < start_cost + 1) continue;
                if (visited[ny][nx] == start_cost + 1 && maps[ny][nx] != maps[sy][sx]) continue;
            }
            // 추가 이동을 해야 하는 경우
            if (abs(ny - sy) + abs(nx - sx) < move) {
                temp_q.push(make_pair(ny, nx));
                result[ny][nx] = player;
                visited[ny][nx] = start_cost + 1;
            }
            // 1이 이동이 끝인 경우
            else {
                q.push(make_pair(ny, nx));
                result[ny][nx] = player;
                visited[ny][nx] = start_cost + 1;
            }
        }
    }
    // 추가 이동이 필요한 경우에 진행
    while(!temp_q.empty()) {
        auto [y, x] = temp_q.front(); temp_q.pop();
        for(int d=0; d<4; d++) {
            int ny = y + moveY[d];
            int nx = x + moveX[d];
            if (check_outside(ny, nx) || result[ny][nx] != 0 || maps[ny][nx] == '#') continue;
            if (result[ny][nx] == 0 || result[ny][nx] == player) {
                if (visited[ny][nx] <= start_cost + 1) {
                    if (visited[ny][nx] < start_cost + 1) continue;
                    if (visited[ny][nx] == start_cost + 1 && maps[ny][nx] != maps[sy][sx]) continue;
                }
                // 추가 이동을 해야 하는 경우
                if (abs(ny - sy) + abs(nx - sx) < move) {
                    temp_q.push(make_pair(ny, nx));
                    result[ny][nx] = player;
                    visited[ny][nx] = start_cost + 1;
                }
                // 1이 이동이 끝인 경우
                else {
                    q.push(make_pair(ny, nx));
                    result[ny][nx] = player;
                    visited[ny][nx] = start_cost + 1;
                }
            }
        }
    }
}

void bfs() {
    while(!q.empty()) {
        auto[y, x] = q.front(); q.pop();
        get_next_position(y, x);
        print_result();
    }
}

int main(){
    cin>>sizeY>>sizeX>>player_cnt;
    move_size.resize(player_cnt + 1, 0);
    players.resize(player_cnt + 1);
    maps.resize(sizeY);
    result.resize(sizeY, vector<int>(sizeX, 0));
    visited.resize(sizeY, vector<int>(sizeX, INF));
    for(int i=1; i<=player_cnt; i++) cin>>move_size[i];
    for(int y=0; y<sizeY; y++) {
        cin>>maps[y];
        for(int x=0; x<sizeX; x++) {
            if (maps[y][x] >= '1' && maps[y][x] <= '9') {
                int player = maps[y][x] - '0';
                players[player].push_back(make_pair(y, x));
                result[y][x] = player;
                visited[y][x] = 0;
            }
        }
    }
    for(int i=1; i<=player_cnt; i++) {
        for(int j=0; j<players[i].size(); j++)
            q.push(make_pair(players[i][j].first, players[i][j].second));
    }
    bfs();
    //print_result();
    find_answer();
}