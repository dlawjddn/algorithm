#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

#define INF 987654321

using namespace std;

struct Info {
    int y, x, cost;
    bool operator<(const Info& other) const {
        return cost > other.cost;
    }
};
int sq_size, moveY[4]={0,1,0,-1}, moveX[4]={1,0,-1,0};
vector<vector<int> > maps;
vector<vector<int> > visited;

bool check_outside(int y, int x) {
    return y < 0 || y >= sq_size || x < 0 || x >= sq_size;
}

int dijkstra() {
    priority_queue<Info> pq;
    pq.push({0,0,maps[0][0]});
    visited[0][0] = maps[0][0];
    while(!pq.empty()) {
        auto[y, x, cost] = pq.top(); pq.pop();
        if (visited[y][x] < cost) continue;
        for(int d=0; d<4; d++) {
            int ny = y + moveY[d];
            int nx = x + moveX[d];
            if (check_outside(ny, nx)) continue;
            int ncost = cost + maps[ny][nx];
            if (visited[ny][nx] <= ncost) continue;
            pq.push({ny, nx, ncost});
            visited[ny][nx] = ncost;
        }
    }
    return visited[sq_size-1][sq_size-1];
}

int main() {
    int test_case; cin>>test_case;
    for(int t=0; t<test_case; t++) {
        cin>>sq_size;
        maps = vector<vector<int> >(sq_size, vector<int>(sq_size, 0));
        visited = vector<vector<int> >(sq_size, vector<int>(sq_size, INF));
        for(int y=0; y<sq_size; y++) {
            for(int x=0; x<sq_size; x++) {
                cin>>maps[y][x];
            }
        }
        cout<<dijkstra()<<"\n";
    }
}