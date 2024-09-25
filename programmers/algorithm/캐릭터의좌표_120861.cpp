/**
 * @file 캐릭터의좌표_120861.cpp
 * @brief 프로그래머스 lv.0 캐릭터의 좌표
 * @version 0.1
 * @date 2024-09-25
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

int minY, maxY, minX, maxX, y = 0, x = 0;
unordered_map<string, pair<int, int> > dir;

void init_dir() {
    dir["left"] = {-1, 0};
    dir["right"] = {1, 0};
    dir["up"] = {0, 1};
    dir["down"] = {0, -1};
}

bool check_outside(int ny, int nx) {
    return ny < minY || ny > maxY || nx < minX || nx > maxX;
}

vector<int> solution(vector<string> keyinput, vector<int> board) {
    minX = -1 * ((board[0] - 1) / 2);
    maxX = (board[0] - 1) / 2;
    minY = -1 * ((board[1] - 1) / 2);
    maxY = (board[1] - 1) / 2;
    init_dir();
    for(auto order : keyinput) {
        int nx = x + dir[order].first;
        int ny = y + dir[order].second;
        if (check_outside(ny, nx)) continue;
        y = ny;
        x = nx;
    }
    return {x, y};
}