#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int sq_size = 0, unit_cnt = 0, moveY[4] = {0, 0, -1, 1}, moveX[4] = {1, -1, 0, 0};
vector<vector<int> > board;
vector<vector<vector<pair<int, int> > > > maps;
queue<pair<int, int> > q;

void print_board() {
    for (int y = 0; y < sq_size; y++) {
        for (int x = 0; x < sq_size; x++) {
            cout << board[y][x] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

string print_dir(int d) {
    if (d == 0) return "->";
    else if (d==1) return "<-";
    else if (d==2) return "^";
    else return "v";
}

void print_maps() {
    for (int y = 0; y < sq_size; y++) {
        for (int x = 0; x < sq_size; x++) {
            if (maps[y][x].size() == 0) continue;
            cout << "(" << y << ", " << x << ")";
            for (auto map : maps[y][x]) {
                cout << "idx: " << map.first+1 << " dir: " << print_dir(map.second) << " // ";
            }
            cout << "\n";
        }
        cout << "\n";
    }
}

bool check_outside(int y, int x) {
    return y < 0 || y >= sq_size || x < 0 || x >= sq_size;
}

int opposite_dir(int d) {
    return (d % 2 == 0) ? d + 1 : d - 1;
}

void move_white(int y, int x, int ny, int nx) {
    maps[ny][nx].insert(maps[ny][nx].end(), maps[y][x].begin(), maps[y][x].end());
    maps[y][x].clear();
}

void move_red(int y, int x, int ny, int nx) {
    maps[ny][nx].insert(maps[ny][nx].end(), maps[y][x].rbegin(), maps[y][x].rend());
    maps[y][x].clear();
    if (maps[ny][nx][0].first < maps[ny][nx][maps[ny][nx].size() - 1].first) {
        q.push(make_pair(ny, nx));
    }
}

bool is_finish(){
    for (int y = 0; y < sq_size; y++) {
        for (int x = 0; x < sq_size; x++) {
            if (maps[y][x].size() >= 4) {
                return true;
            }
        }
    }
    return false;
}

int bfs() {
    int turn = 0;
    while (turn < 1000) {
        ++turn;
        cout << "turn: " << turn << "\n";
        vector<pair<int, int> > next;
        while (!q.empty()) {
            int y = q.front().first;
            int x = q.front().second; q.pop();

            if (maps[y][x].size() == 0) continue;
            int d = maps[y][x][0].second;

            int ny = y + moveY[d];
            int nx = x + moveX[d];

            if (check_outside(ny, nx) || board[ny][nx] == 2) {
                int other_d = opposite_dir(d);
                maps[y][x][0].second = other_d;

                ny = y + moveY[other_d];
                nx = x + moveX[other_d];

                if (check_outside(ny, nx) || board[ny][nx] == 2) {
                    next.push_back(make_pair(y, x));
                } else {
                    if (board[ny][nx] == 0) move_white(y, x, ny, nx);
                    else move_red(y, x, ny, nx);
                    next.push_back(make_pair(ny, nx));
                }
            } else {
                if (board[ny][nx] == 0) move_white(y, x, ny, nx);
                else move_red(y, x, ny, nx);
                next.push_back(make_pair(ny, nx));
            }
            if (is_finish()) return turn;
        }
        

        for (auto n : next) q.push(n);
        print_maps();
    }
    return -1;
}

int main() {
    cin >> sq_size >> unit_cnt;
    board.resize(sq_size, vector<int>(sq_size));
    maps.resize(sq_size, vector<vector<pair<int, int> > >(sq_size));

    for (int y = 0; y < sq_size; y++) {
        for (int x = 0; x < sq_size; x++) {
            cin >> board[y][x];
        }
    }

    for (int i = 0; i < unit_cnt; i++) {
        int y, x, dir;
        cin >> y >> x >> dir;
        q.push(make_pair(y - 1, x - 1));
        maps[y - 1][x - 1].push_back(make_pair(i, dir - 1));
    }

    cout << "turn: 0\n";
    print_maps();
    cout << bfs();
}
