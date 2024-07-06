#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define BOARD_SIZE 1010
#define x first
#define y second

char board[BOARD_SIZE][BOARD_SIZE];
int step[11];
int castle[11];
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, -1, 0, 1};
int n, m, p;

int main() {
    cin >> n >> m >> p;

    for (int i = 1; i <= p; i++) 
        cin >> step[i];

    vector<pair<int, int>> pos[p + 1];
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> board[i][j];
            if (board[i][j] != '.' && board[i][j] != '#') {
                pos[board[i][j] - '0'].push_back({i, j});
            }
        }
    }

    bool end = false;
    while (!end) {
        int totalCnt = 0;
        for (int player = 1; player <= p; player++) {
            for (int i = 0; i < step[player]; i++) {
                bool stop = true;
                vector<pair<int, int>> v;
                for (auto c : pos[player]) {
                    for (int dir = 0; dir < 4; dir++) {
                        int nx = c.x + dx[dir];
                        int ny = c.y + dy[dir];

                        if (nx < 0 || ny < 0 || nx >= n || ny >= m) continue;
                        if (board[nx][ny] != '.') continue;

                        totalCnt++;
                        stop = false;
                        v.push_back({nx, ny});
                        board[nx][ny] = player + '0';
                    }
                }
                if (stop) break;
                pos[player] = v;
            }
        }
        if (totalCnt == 0) end = true;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (board[i][j] >= '0' && board[i][j] <= '9') {
                castle[board[i][j] - '0']++;
            }
        }
    }

    for (int i = 1; i <= p; i++) 
        cout << castle[i] << " ";

    return 0;
}
