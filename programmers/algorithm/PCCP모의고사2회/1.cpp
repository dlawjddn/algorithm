/**
 * @file 1.cpp
 * @brief PCCP 모의고사 2회 1번
 * @version 0.1
 * @date 2024-08-31
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <string>
#include <vector>

using namespace std;

// 북: 0
// 동: 1
// 남: 2
// 서: 3

int moveY[4]={1, 0, -1, 0}, moveX[4]={0,1,0,-1};

int change_dir(int dir, char command) {
    if (command == 'R') {
        return (dir + 1) % 4;
    }
    return (dir + 3) % 4;
}

vector<int> solution(string command) {
    int y = 0, x = 0, dir = 0;
    for(int i=0; i<command.size(); i++) {
        char cmd = command[i];
        if (cmd == 'R' || cmd == 'L') {
            dir = change_dir(dir, cmd);
            continue;
        }
        else {
            if (cmd == 'G') {
                y += moveY[dir];
                x += moveX[dir];
            } else {
                y -= moveY[dir];
                x -= moveX[dir];
            }
        }
    }
    return {x, y};
}