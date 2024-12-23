#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int sq_size, moveY[4]={0,1,0,-1}, moveX[4]={1,0,-1,0};
bool finish = false;
vector<vector<char> > maps;
vector<pair<int, int> > teachers;
vector<pair<int, int> > emptys;
vector<bool> visited;

bool check_outside(int y, int x) {
    return y < 0 || y >= sq_size || x < 0 || x >= sq_size;
}

bool observe_students() {
    for(int i=0; i<teachers.size(); i++) {
        auto[sy, sx] = teachers[i];
        for(int d=0; d<4; d++) {
            int y = sy, x = sx;
            while(1) {
                int ny = y + moveY[d];
                int nx = x + moveX[d];
                if (check_outside(ny, nx) || maps[ny][nx] == 'O') break;
                if (maps[ny][nx] == 'S') return false;
                y = ny;
                x = nx;
            }
        }
    }
    return true;
}

void change_state(vector<int>& chosen) {
    for(int i=0; i<chosen.size(); i++) {
        auto[y, x] = emptys[chosen[i]];
        maps[y][x] = (maps[y][x] == 'X') ? 'O' : 'X';
    }
}

void combination(int idx, int depth, vector<int>& chosen) {
    if (depth == 3) {
        change_state(chosen);
        if (observe_students()) {
            finish = true;
            return ;
        }
        change_state(chosen);
        return ;
    }
    for(int i = idx; i<emptys.size(); i++) {
        if (visited[i]) continue;
        visited[i] = true;
        chosen.push_back(i);
        combination(i, depth+1, chosen);
        chosen.pop_back();
        visited[i] = false;
        if (finish) return ;
    }
}

int main() {
    cin>>sq_size;
    maps.resize(sq_size, vector<char>(sq_size));
    for(int y=0; y<sq_size; y++) {
        for(int x=0; x<sq_size; x++) {
            cin>>maps[y][x];
            if (maps[y][x] == 'T') teachers.push_back({y, x});
            else if (maps[y][x] == 'X') emptys.push_back({y, x});
        }
    }
    vector<int> chosen;
    visited.resize(emptys.size(), false);
    combination(0, 0, chosen);
    cout<<((finish) ? "YES" : "NO"); 
}