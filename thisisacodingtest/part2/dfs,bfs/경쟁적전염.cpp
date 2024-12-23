#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct Info {
    int y, x, id, time;
    bool operator<(Info other) const {
        if (time == other.time) {
            return id > other.id;
        } return time > other.time;
    }
};
int sq_size, virus_cnt, moveY[4]={0,1,0,-1}, moveX[4]={1,0,-1,0};
int second, destY, destX;
vector<vector<int> > virus_pos;
priority_queue<Info> pq;

void print_map() {
    for(int y=0; y<sq_size; y++) {
        for(int x=0; x<sq_size; x++) {
            cout<<virus_pos[y][x]<<" ";
        }
        cout<<"\n";
    }
}

bool check_outside(int y, int x) {
    return y < 0 || y >= sq_size || x < 0 || x >= sq_size;
}


void bfs() {
    while(!pq.empty() && pq.top().time < second) {
        auto[y, x, id, time] = pq.top(); pq.pop();
        if (virus_pos[y][x] != id) continue;
        for(int d=0; d<4; d++) {
            int ny = y + moveY[d];
            int nx = x + moveX[d];
            int ntime = time + 1;
            if (check_outside(ny, nx) || virus_pos[ny][nx] != 0) continue;
            pq.push({ny, nx, id, ntime});
            virus_pos[ny][nx] = id;
        }
    }
}

int main() {
    cin>>sq_size>>virus_cnt;
    virus_pos.resize(sq_size, vector<int>(sq_size, 0));
    for(int y=0; y<sq_size; y++) {
        for(int x=0; x<sq_size; x++) {
            cin>>virus_pos[y][x];
            if (virus_pos[y][x] != 0) {
                pq.push({y, x, virus_pos[y][x], 0});
            }
        }
    }
    cin>>second>>destY>>destX;
    bfs();
    cout<<virus_pos[destY-1][destX-1];
}