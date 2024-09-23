/**
 * @file 삼각달팽이_68645.cpp
 * @brief 프로그래머스 lv.2 삼각달팽이 
 * @version 0.1
 * @date 2024-09-23
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <string>
#include <vector>
#include <iostream>

using namespace std;

vector<vector<int> > maps;

void print_maps() {
    for (int i = 0; i < maps.size(); i++) {
        for (int j = 0; j < maps[i].size(); j++) {
            cout << maps[i][j] << " ";
        }
        cout << "\n";
    }
}

vector<int> solution(int n) {
    vector<int> answer;
    maps.resize(n); 
    for(int i=0; i<n; i++) {
        maps[i].resize(i+1);
    }
    int stage = 0;
    int x = 0;
    int floor = -1;
    int number = 1;
    
    for (int stage = 0; stage < n; stage++) {
        if (stage % 3 == 0) { // 내려가면서 추가하기
            for (int j = stage; j < n; j++) {
                maps[++floor][x] = number++;
            }
        }
        else if (stage % 3 == 1) { // 같은 층에 추가하기
            for (int j = stage; j < n; j++) {
                maps[floor][++x] = number++;
            }
        }
        else { // 올라가면서 추가하기
            for (int j = stage; j < n; j++) {
                maps[--floor][--x] = number++;
            }
        }
    }
    for(int i=0; i<maps.size(); i++) {
        for(int j=0; j<maps[i].size(); j++) {
            answer.push_back(maps[i][j]);
        }
    }
    return answer;
}