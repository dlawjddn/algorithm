#include <string>
#include <vector>
#include <algorithm>
#include <queue>

#define INF 987654321

using namespace std;

struct Info {
    int y, x, dir, cost;
    bool operator<(Info other) const {
        return cost > other.cost;
    }
};
int moveY[4]={0,1,0,-1}, moveX[4]={1,0,-1,0};
vector<vector<vector<int> > > visited;

Info make_info(int y, int x, int d, int cost) {
    Info info;
    info.y = y;
    info.x = x;
    info.dir = d;
    info.cost = cost;
    return info;
}

bool check_outside(int y, int x) {
    return y < 0 || y >= visited.size() || x < 0 || x >= visited[y].size();
}

int dijkstra(vector<vector<int>>& board) {
    priority_queue<Info> pq;
    for(int d=0; d<4; d++) {
        pq.push(make_info(0, 0, d, 0));
        visited[0][0][d] = 0;
    }
    while(!pq.empty()) {
        auto[y, x, dir, cost] = pq.top(); pq.pop();
        if (visited[y][x][dir] != cost) continue;
        for(int d=0; d<4; d++) {
            int ny = y + moveY[d];
            int nx = x + moveX[d];
            int ncost = (dir == d) ? cost + 100 : cost + 600;
            int ndir = d;
            if (check_outside(ny, nx) || board[ny][nx] == 1 || visited[ny][nx][ndir] <= ncost) continue;
            pq.push(make_info(ny, nx, ndir, ncost));
            visited[ny][nx][ndir] = ncost;
        }
    }
    return *min_element(visited[visited.size()-1][visited[0].size() - 1].begin(), visited[visited.size()-1][visited[0].size() - 1].end());
}

int solution(vector<vector<int>> board) {
    int answer = 0;
    visited.resize(board.size(), vector<vector<int>>(board[0].size(), vector<int>(4, INF)));
    return dijkstra(board);
}