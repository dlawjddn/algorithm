#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <iostream>

#define INF 987654321

using namespace std;

struct Info {
    pair<int, int> pos1;
    pair<int, int> pos2;
    int time;
    bool operator<(Info other) const {
        return time > other.time;
    }
};

int sizeY, sizeX, moveY[4] = {0, 1, 0, -1}, moveX[4] = {1, 0, -1, 0};
vector<vector<int>> cost;
vector<vector<vector<vector<int>>>> visited;

Info make_info(int y1, int x1, int y2, int x2, int time) {
    return {{y1, x1}, {y2, x2}, time};
}

void save_cost(int y1, int x1, int y2, int x2, int time) {
    cost[y1][x1] = min(cost[y1][x1], time);
    cost[y2][x2] = min(cost[y2][x2], time);
}

bool check_outside(int y, int x) {
    return y < 0 || y >= sizeY || x < 0 || x >= sizeX;
}

void bfs(const vector<vector<int>> &board) {
    priority_queue<Info> pq;
    pq.push(make_info(0, 0, 0, 1, 0));
    visited[0][0][0][1] = 0;
    save_cost(0, 0, 0, 1, 0);

    while (!pq.empty()) {
        auto [p1, p2, time] = pq.top();
        pq.pop();
        auto [y1, x1] = p1;
        auto [y2, x2] = p2;

        if (visited[y1][x1][y2][x2] < time) continue;

        // 이동
        for (int i = 0; i < 4; ++i) {
            int ny1 = y1 + moveY[i], nx1 = x1 + moveX[i];
            int ny2 = y2 + moveY[i], nx2 = x2 + moveX[i];
            int ntime = time + 1;

            if (!check_outside(ny1, nx1) && !check_outside(ny2, nx2) &&
                board[ny1][nx1] == 0 && board[ny2][nx2] == 0 &&
                visited[ny1][nx1][ny2][nx2] > ntime) {
                pq.push(make_info(ny1, nx1, ny2, nx2, ntime));
                visited[ny1][nx1][ny2][nx2] = ntime;
                save_cost(ny1, nx1, ny2, nx2, ntime);
            }
        }

        // 회전
        if (y1 == y2) { // 가로 방향
            for (int d = -1; d <= 1; d += 2) {
                if (!check_outside(y1 + d, x1) && !check_outside(y2 + d, x2) &&
                    board[y1 + d][x1] == 0 && board[y2 + d][x2] == 0) {
                    int ntime = time + 1;

                    if (visited[y1][x1][y1 + d][x1] > ntime) {
                        pq.push(make_info(y1, x1, y1 + d, x1, ntime));
                        visited[y1][x1][y1 + d][x1] = ntime;
                        save_cost(y1, x1, y1 + d, x1, ntime);
                    }
                    if (visited[y2][x2][y2 + d][x2] > ntime) {
                        pq.push(make_info(y2, x2, y2 + d, x2, ntime));
                        visited[y2][x2][y2 + d][x2] = ntime;
                        save_cost(y2, x2, y2 + d, x2, ntime);
                    }
                }
            }
        } else { // 세로 방향
            for (int d = -1; d <= 1; d += 2) {
                if (!check_outside(y1, x1 + d) && !check_outside(y2, x2 + d) &&
                    board[y1][x1 + d] == 0 && board[y2][x2 + d] == 0) {
                    int ntime = time + 1;

                    if (visited[y1][x1][y1][x1 + d] > ntime) {
                        pq.push(make_info(y1, x1, y1, x1 + d, ntime));
                        visited[y1][x1][y1][x1 + d] = ntime;
                        save_cost(y1, x1, y1, x1 + d, ntime);
                    }
                    if (visited[y2][x2][y2][x2 + d] > ntime) {
                        pq.push(make_info(y2, x2, y2, x2 + d, ntime));
                        visited[y2][x2][y2][x2 + d] = ntime;
                        save_cost(y2, x2, y2, x2 + d, ntime);
                    }
                }
            }
        }
    }
}

int solution(vector<vector<int>> board) {
    sizeY = board.size();
    sizeX = board[0].size();
    cost.resize(sizeY, vector<int>(sizeX, INF));
    visited.resize(sizeY, vector<vector<vector<int>>>(sizeX, vector<vector<int>>(sizeY, vector<int>(sizeX, INF))));

    bfs(board);
    
    // for(int y=0; y<sizeY; y++) {
    //     for(int x=0; x<sizeX; x++) {
    //         cout<<cost[y][x]<<" ";
    //     }
    //     cout<<"\n";
    // }

    return cost[sizeY - 1][sizeX - 1];
}
