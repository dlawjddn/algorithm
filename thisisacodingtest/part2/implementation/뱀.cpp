#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct Info {
    int y, x, dir, len, timer;
};
int sq_size, apple_cnt, move_cnt, moveY[4] = {0,1,0,-1}, moveX[4] = {1,0,-1,0};
vector<vector<bool> > apple;
vector<vector<int> > move_history;
vector<pair<int, char> > change;

void print_move() {
    for(int y=0; y<sq_size; y++) {
        for(int x=0; x<sq_size; x++) {
            cout<<move_history[y][x] + 1<<" ";
        }
        cout<<"\n";
    }
}

void init() {
    apple.resize(sq_size, vector<bool>(sq_size, false));
    move_history.resize(sq_size, vector<int>(sq_size, -1));
}

bool check_outside(int y, int x) {
    return y < 0 || y >= sq_size || x < 0 || x >= sq_size;
}

bool check_body(int y, int x, int ny, int nx, int len) {
    if (move_history[ny][nx] == -1) return false;
    else if (abs(move_history[y][x] - move_history[ny][nx]) >= len) return false;
    return true;
}

int change_dir(int dir, char ndir) {
    if (ndir == 'L') return (dir + 3) % 4;
    else return (dir + 1) % 4;
}

int move() {
    int result = 0;
    queue<Info> q;
    q.push({0,0,0,1,0});
    move_history[0][0] = 0;
    while(!q.empty()) {
        auto[y, x, d, len, time] = q.front(); q.pop();

        int ny = y + moveY[d];
        int nx = x + moveX[d];
        int nd = d;
        int nlen = len;
        int ntime = time + 1;

        if (check_outside(ny, nx) || check_body(y, x, ny, nx, len)) break;

        if (apple[ny][nx]) {
            nlen++;
            apple[ny][nx] = false;
        }

        if (change.back().first == ntime) {
            nd = change_dir(nd, change.back().second);
            change.pop_back();
        }

        q.push({ny, nx, nd, nlen, ntime});
        move_history[ny][nx] = ntime;
        result++;
    }
    return result;
}

int main() {
    cin>>sq_size;
    init();
    cin>>apple_cnt;
    for(int i=0; i<apple_cnt; i++) {
        int y, x; cin>>y>>x;
        apple[y-1][x-1] = true;
    }
    cin>>move_cnt;
    for(int i=0; i<move_cnt; i++) {
        int time; char dir; cin>>time>>dir;
        change.push_back({time, dir});
    }
    reverse(change.begin(), change.end());
    cout<<move() + 1<<"\n";
    //print_move();
}