/**
 * @file boj_14499.cpp
 * @brief 백준 gold4 주사위 굴리기
 * @version 0.1
 * @date 2024-08-04
 * 
 * @copyright Copyright (c) 2024
 * 
 * 주사위는 그냥 벡터 배열 만들어서 간단하게 하자..
 * 
 */
#include <iostream>
#include <vector>

using namespace std;

int sizeY, sizeX, sy, sx, order_cnt;
int moveY[5] = {0, 0, 0, -1, 1}; // 명령에 따른 y 좌표 이동: 동, 서, 북, 남
int moveX[5] = {0, 1, -1, 0, 0}; // 명령에 따른 x 좌표 이동: 동, 서, 북, 남
vector<int> dice(7, 0); // 주사위 각 면의 값
vector<vector<int>> maps;
vector<vector<int>> next_pos = {
    {},
    {0, 4, 2, 1, 6, 5, 3}, // 동
    {0, 3, 2, 6, 1, 5, 4}, // 서
    {0, 5, 1, 3, 4, 6, 2}, // 북
    {0, 2, 6, 3, 4, 1, 5}  // 남
};

void roll_dice(int dir) {
    vector<int> temp(7);
    for (int i = 1; i <= 6; i++) {
        temp[i] = dice[i];
    }
    for (int i = 1; i <= 6; i++) {
        dice[i] = temp[next_pos[dir][i]];
    }
}

bool check_outside(int y, int x) {
    return y < 0 || y >= sizeY || x < 0 || x >= sizeX;
}

int main() {
    cin >> sizeY >> sizeX >> sy >> sx >> order_cnt;
    maps.resize(sizeY, vector<int>(sizeX, 0));
    for (int y = 0; y < sizeY; y++) {
        for (int x = 0; x < sizeX; x++) {
            cin >> maps[y][x];
        }
    }

    vector<int> orders(order_cnt);
    for (int i = 0; i < order_cnt; i++) {
        cin >> orders[i];
    }

    int y = sy, x = sx;
    for (int i = 0; i < order_cnt; i++) {
        int dir = orders[i];
        int ny = y + moveY[dir];
        int nx = x + moveX[dir];

        if (check_outside(ny, nx)) continue; // 지도 밖으로 나가는 명령은 무시

        roll_dice(dir); // 주사위 굴리기

        if (maps[ny][nx] == 0) {
            maps[ny][nx] = dice[6]; // 이동한 칸의 수가 0이면 주사위 바닥면의 수를 칸에 복사
        } else {
            dice[6] = maps[ny][nx]; // 이동한 칸의 수가 0이 아니면 칸의 수를 주사위 바닥면으로 복사
            maps[ny][nx] = 0; // 칸의 수는 0으로 변경
        }

        cout << dice[1] << endl; // 주사위 윗면의 수 출력

        y = ny;
        x = nx;
    }

    return 0;
}
