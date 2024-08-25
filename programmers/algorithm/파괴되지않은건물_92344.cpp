/**
 * @file 파괴되지않은건물_92344.cpp
 * @brief 프로그래머스 lv.3 카카오 2022 공채 파괴되지 않은 건물
 * @version 0.1
 * @date 2024-08-25
 * 
 * @copyright Copyright (c) 2024
 * 
 * 구간합.. 아이디어가 중요한 문제
 */
#include <string>
#include <vector>
#include <iostream>

using namespace std;

vector<vector<int> > diff;

bool check_outside(int y, int x) {
    return y < 0 || y >= diff.size() || x < 0 || x >= diff[0].size();
}

int solution(vector<vector<int>> board, vector<vector<int>> skill) {
    int answer = 0;
    diff.resize(board.size(), vector<int>(board[0].size(), 0));
    for(auto s : skill) {
        int type = s[0];
        int sy = s[1];
        int sx = s[2];
        int dy = s[3];
        int dx = s[4];
        int degree = s[5];
        if (type == 1) { // 적의 공격
            diff[sy][sx] += -1 * degree;
            if (!check_outside(sy, dx + 1)) diff[sy][dx + 1] += degree;
            if (!check_outside(dy + 1, sx)) diff[dy + 1][sx] += degree;
            if (!check_outside(dy + 1, dx + 1)) diff[dy + 1][dx + 1] += -1 *degree;
        }
        else { // 아군의 회복 스킬
            diff[sy][sx] += degree;
            if (!check_outside(sy, dx + 1)) diff[sy][dx + 1] += -1 * degree;
            if (!check_outside(dy + 1, sx)) diff[dy + 1][sx] += -1 * degree;
            if (!check_outside(dy + 1, dx + 1)) diff[dy + 1][dx + 1] += degree;
        }
    }
    for(int y=0; y<diff.size(); y++) {
        for(int x=1; x<diff[y].size(); x++) {
            diff[y][x] += diff[y][x-1];
        }
    }
    for(int x=0; x<diff[0].size(); x++) {
        for(int y=1; y<diff.size(); y++) {
            diff[y][x] += diff[y-1][x];
        }
    }
    for(int y=0; y<diff.size(); y++) {
        for(int x=0; x<diff[y].size(); x++) {
            if (board[y][x] + diff[y][x] > 0) answer++;
        }
    }
    return answer;
}