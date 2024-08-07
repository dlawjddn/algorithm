/**
 * @file temp.cpp
 * @author your name (you@domain.com)
 * @brief 프로그래머스 lv.2 2021 Dev-Matching: 웹 백엔드 개발자(상반기) 행렬 테두리 회전하기
 * @version 0.1
 * @date 2024-08-07
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

vector<vector<int> > maps;

void print_map() {
    for(int y=0; y<maps.size(); y++) {
        for(int x=0; x<maps[y].size(); x++) {
            cout<<maps[y][x]<<" ";
        }
        cout<<"\n";
    }
}

void fill_map(int sizeY, int sizeX) {
    maps.resize(sizeY, vector<int>(sizeX, 0));
    for(int y=0; y<sizeY; y++) {
        for(int x=0; x<sizeX; x++) {
            maps[y][x] = y * sizeX + x + 1;
        }
    }
}

int change_map(int sy, int sx, int dy, int dx) {
    vector<int> numbers;
    // 윗변
    for(int x = sx; x <= dx; x++) {
        numbers.push_back(maps[sy][x]);
    }
    // 오른쪽 변
    for(int y = sy + 1; y <= dy; y++) {
        numbers.push_back(maps[y][dx]);
    }
    // 밑변
    for(int x = dx - 1; x >= sx; x--) {
        numbers.push_back(maps[dy][x]);
    }
    // 왼쪽 변
    for(int y = dy - 1; y > sy; y--) {
        numbers.push_back(maps[y][sx]);
    }
    
    int idx = 0;
    // 윗변
    for(int x = sx+1; x<=dx; x++) {
        maps[sy][x] = numbers[idx++];
    }
    
    // 오른변
    for(int y=sy+1; y<=dy; y++) {
        maps[y][dx] = numbers[idx++];
    }
    
    // 밑변
    for(int x=dx-1; x>=sx; x--) {
        maps[dy][x] = numbers[idx++];
    }
    
    // 왼쪽변
    for(int y=dy-1; y>=sy; y--) {
        maps[y][sx] = numbers[idx++];
    }
    maps[sy][sx] = numbers.back();
    
    return *min_element(numbers.begin(), numbers.end());
}

vector<int> solution(int rows, int columns, vector<vector<int>> queries) {
    vector<int> answer;
    fill_map(rows, columns);
    for(auto query : queries) {
        int sy = query[0] - 1;
        int sx = query[1] - 1;
        int dy = query[2] - 1;
        int dx = query[3] - 1;
        answer.push_back(change_map(sy, sx, dy, dx));
    }
    return answer;
}