#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct Info {
    int y, x, dir, cnt;
};
int sizeY, sizeX, sy, sx, dy, dx, road_cnt, moveY[4]={0,1,0,-1}, moveX[4]={1,0,-1,0};
vector<string> maps;
vector<pair<int, int> > emptys;
vector<vector<vector<bool> > > visited;
vector<char> blocks = {'|', '-', '+', '1', '2', '3', '4'};

Info make_info(int y, int x, int dir, int cnt) {
    Info info;
    info.y = y;
    info.x = x;
    info.dir = dir;
    info.cnt = cnt;
    return info;   
}

bool check_outside(int y, int x) {
    return y < 0 || y >= sizeY || x < 0 || x >= sizeX;
}

bool is_avilable(char symbol, int d) {
    if (symbol == '|' && (d == 1 || d == 3)) return true;
    else if (symbol == '-' && (d == 0 || d == 2)) return true;
    else if (symbol == '+' || symbol == 'Z') return true;
    else if (symbol == '1' && (d == 2 || d == 3)) return true;
    else if (symbol == '2' && (d == 1 || d == 2)) return true;
    else if (symbol == '3' && (d == 0 || d == 1)) return true;
    else if (symbol == '4' && (d == 0 || d == 3)) return true;
    return false;
}

int get_next_direction(char symbol, int d) {
    if (symbol == '|') return (d == 1) ? 1 : 3;
    else if (symbol == '-') return (d == 0) ? 0 : 2;
    else if (symbol == '1') return (d == 2) ? 1 : 0;
    else if (symbol == '2') return (d == 1) ? 0 : 3;
    else if (symbol == '3') return (d == 0) ? 3 : 2;
    else if (symbol == '4') return (d == 0) ? 1 : 2;
}

void print_visited() {
    for(int cnt = 0; cnt < road_cnt; cnt++) {
        for(int y=0; y<sizeY; y++) {
            for(int x=0; x<sizeX; x++) {
                if (visited[y][x][cnt]) {
                    cout<<"("<<y<<" "<<x<<") ";
                }
            }
        }
    }
}

bool bfs() {
    queue<Info> q;
    vector<int> result;
    for(int d=0; d<4; d++) {
        q.push(make_info(sy, sx, d, 0));
    }
    while(!q.empty()) {
        auto[y, x, d, cnt] = q.front(); q.pop();
        if (y == dy && x == dx) result.push_back(cnt);
        int ny = y + moveY[d];
        int nx = x + moveX[d];
        int ncnt = cnt + 1;
        // 격자 범위 안, 다음 블록으로 갈 수 있는지 여부 확인
        if (check_outside(ny, nx) || !is_avilable(maps[ny][nx], d)) continue;

        // 다음 블록으로 인한 방향 변경 적용
        if (maps[ny][nx] == '+') {
            for(int d=0; d<4; d++) {
                if (ncnt >= road_cnt) continue;
                q.push(make_info(ny, nx, d, ncnt));
            }
        } else if (maps[ny][nx] == 'Z') {
            q.push(make_info(ny, nx, d, ncnt));
        } else {
            int nd = get_next_direction(maps[ny][nx], d);
            if (ncnt >= road_cnt) continue;
            q.push(make_info(ny, nx, nd, ncnt));
        }
    }
    for(auto r : result) {
        cout<<r<<" ";
    }
    cout<<"\n";
    return false;
}

void solve() {
    for(auto empty : emptys) {
        for(auto block : blocks) {
            maps[empty.first][empty.second] = block;
            bool result = bfs();
            cout<<"("<<empty.first<<" "<<empty.second<<") "<<"block: "<<block<<"\n";
            cout<<"\n\n";
            if (result) {
                cout<<empty.first + 1<<" "<<empty.second + 1<<" "<<block;
                return ;
            }
        }
        maps[empty.first][empty.second] = '.';
    }
}

int main(){
    cin>>sizeY>>sizeX;
    maps.resize(sizeY);
    for(int y=0; y<sizeY; y++) {
        cin>>maps[y];
        for(int x=0; x<sizeX; x++) {
            if (maps[y][x] == 'M') {
                sy = y;
                sx = x;
            } else if (maps[y][x] == 'Z') {
                dy = y;
                dx = x;
            } else if (maps[y][x] == '.') emptys.push_back({y, x});
        }
    }
    road_cnt = sizeY * sizeX - emptys.size() + 1;
    cout<<emptys.size()<<"\n";
    solve();
}