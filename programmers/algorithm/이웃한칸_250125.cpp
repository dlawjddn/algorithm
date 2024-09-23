/**
 * @file 이웃한칸_250125.cpp
 * @brief 프로그래머스 lv.1 이웃한 칸
 * @version 0.1
 * @date 2024-09-23
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <string>
#include <vector>

using namespace std;


int sizeY=0, sizeX=0, moveY[4]={0,1,0,-1}, moveX[4]={1,0,-1,0};

bool check_outside(int y, int x) {
    return y < 0 || y >= sizeY || x < 0 || x >= sizeX;
}

int solution(vector<vector<string>> board, int h, int w) {
    int answer = 0;
    sizeY = board.size();
    sizeX = board[0].size();
    int y = h;
    int x = w;
    for(int d=0; d<4; d++) {
        int ny = y + moveY[d];
        int nx = x + moveX[d];
        if (check_outside(ny, nx)) continue;
        if (board[y][x] == board[ny][nx]) answer++;
    }
    return answer;
}