#include <iostream>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;

struct Point {
    int y, x, time;

    Point(int y, int x, int time) : y(y), x(x), time(time) {}
};

struct Signal {
    int sn, we;
    bool sn_first;
};

char map[20][20];
int visited[20][20], moveY[4] = {0, 1, 0, -1}, moveX[4] = {1, 0, -1, 0}, sizeY = 0, sizeX = 0, cross = -1;
Signal signals[10];

int truck_shipping(Point start) {
    queue<Point> q;
    q.push(start);
    visited[start.y][start.x] = start.time;

    while(!q.empty()) {
        Point now = q.front(); q.pop();
        if (map[now.y][now.x] == 'B') {
            return now.time - 1;
        }
        for (int d = 0; d < 4; d++) {
            int ny = now.y + moveY[d];
            int nx = now.x + moveX[d];
            int ntime = now.time + 1;

            if (ny >= 0 && ny < sizeY && nx >= 0 && nx < sizeX && map[ny][nx] != '.' && visited[ny][nx] == 0) {
                if (map[ny][nx] == '#' || map[ny][nx] == 'B') {
                    q.push(Point(ny, nx, ntime));
                    visited[ny][nx] = ntime;
                } else if (map[ny][nx] >= '0' && map[ny][nx] <= '9') {
                    int signal_idx = map[ny][nx] - '0';
                    Signal s = signals[signal_idx];
                    int cal = now.time % (s.sn + s.we);
                    if (s.sn_first){
                        if (cal != 0 && cal <= s.sn){ // 남북 방향
                            if (d == 1 || d == 3){
                                q.push(Point(ny, nx, ntime));
                                visited[ny][nx] = ntime;
                                continue;
                            }
                        } else {
                            if (d == 0 || d == 2){
                                q.push(Point(ny, nx, ntime));
                                visited[ny][nx] = ntime;
                                continue;
                            }
                        }
                    } else {
                        if (cal != 0 && cal <= s.we){
                            if (d == 0 || d == 2){
                                q.push(Point(ny, nx, ntime));
                                visited[ny][nx] = ntime;
                                continue;
                            }
                        } else {
                            if (d == 1 || d == 3){
                                q.push(Point(ny, nx, ntime));
                                visited[ny][nx] = ntime;
                                continue;
                            }
                        }
                    }
                    q.push(Point(now.y, now.x, ntime));
                    visited[now.y][now.x] = ntime;
                }
            }
        }
    }
    return -1;
}

int main() {
    while (1) {
        int startY, startX;
        cin >> sizeY >> sizeX;
        if (sizeY == 0 && sizeX == 0) break;

        for (int i = 0; i < sizeY; i++) {
            string s;
            cin >> s;
            for (int j = 0; j < sizeX; j++) {
                map[i][j] = s[j];
                if (map[i][j] == 'A') {
                    startY = i;
                    startX = j;
                }
                if (map[i][j] >= '0' && map[i][j] <= '9') {
                    cross = max(cross, map[i][j] - '0');
                }
            }
        }

        for (int i = 0; i <= cross; i++) {
            int num, sn, we;
            char temp_start;
            bool first;
            cin >> num >> temp_start >> we >> sn;

            if (temp_start == '|') {
                signals[num].sn = sn;
                signals[num].we = we;
                signals[num].sn_first = true;
            } else {
                signals[num].sn = sn;
                signals[num].we = we;
                signals[num].sn_first = false;
            }
        }
        int ans = truck_shipping(Point(startY, startX, 1));
        if (ans == -1) cout<<"impossible\n";
        else cout<<ans<<"\n";
        cross = 0;
        memset(map, 0, sizeof(map));
        memset(visited, 0, sizeof(visited));
        memset(signals, 0, sizeof(signals));
    }

    return 0;
}
