/**
 * @file boj_2469.cpp
 * @brief 백준 gold5 사다리 타기
 * @version 0.1
 * @date 2024-07-25
 * 
 * @copyright Copyright (c) 2024
 * 
 * 너무 어렵게 생각하나...
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int sizeX, sizeY, change_pos;
string start;
string goal;
vector<string> maps;

int main(){
    cin>>sizeX>>sizeY>>goal;
    maps.resize(sizeY);
    for(int i=0; i<sizeX; i++) start += (i + 'A');
    for(int i=0; i<sizeY; i++) {
        cin>>maps[i];
        if (maps[i][0] == '?') change_pos = i;
    }
    for(int y=0; y<change_pos; y++) {
        for(int x=0; x<maps[y].size(); x++) {
            if (maps[y][x] == '-') swap(start[x], start[x+1]);
        }
    }
    for(int y=sizeY-1; y>change_pos; y--) {
        for(int x=0; x<maps[y].size(); x++) {
            if (maps[y][x] == '-') swap(goal[x], goal[x+1]);
        }
    }
    string answer = "";
    for(int i=0; i<sizeX-1; i++) {
        if (start[i] == goal[i]) answer += "*";
        else if (start[i] == goal[i+1] && start[i+1] && goal[i]) {
            swap(start[i], start[i+1]);
            answer+='-';
        }
        else {
            answer = string(sizeX - 1, 'x');
            break;
        }
    }
    cout<<answer;
}
