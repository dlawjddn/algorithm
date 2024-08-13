/**
 * @file 단체사진찍기_1835.cpp
 * @brief 프로그래머스 lv.2 2017 카카오코드 단체 사진 찍기
 * @version 0.1
 * @date 2024-08-13
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>

using namespace std;

int convert_to_idx(char symbol) {
    if (symbol == 'A') return 0;
    if (symbol == 'C') return 1;
    if (symbol == 'F') return 2;
    if (symbol == 'J') return 3;
    if (symbol == 'M') return 4;
    if (symbol == 'N') return 5;
    if (symbol == 'R') return 6;
    return 7;
}

int solution(int n, vector<string> data) {
    int answer = 0;
    vector<int> friends;
    
    for(int i=0; i<8; i++) friends.push_back(i);
    do {
        bool success = true;
        for(auto condition : data) {
            int friend1_pos = friends[convert_to_idx(condition[0])];
            int friend2_pos = friends[convert_to_idx(condition[2])];
            char symbol = condition[3];
            int number = condition[4] - '0';
            
            if (symbol == '=' && abs(friend1_pos - friend2_pos) - 1 == number) { // 위치 차이가 number와 같다
                continue;
            } else if (symbol == '<' && abs(friend1_pos - friend2_pos) - 1 < number) { // 위치 차이가 number 미만이다
                continue;
            } else if (symbol == '>' && abs(friend1_pos - friend2_pos) - 1 > number) { // 위치 차이가 number 초과이다
                continue;
            } else { // 해당 조건에 맞지 않음
                success = false;
                break;
            }
        } 
        if (success) answer++;
        
    }while(next_permutation(friends.begin(), friends.end()));
    
    return answer;
}