/**
 * @file 주사위게임1_181839.cpp
 * @brief 프로그래머스 lv.0 주사위 게임 1
 * @version 0.1
 * @date 2024-09-23
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <string>
#include <vector>
#include <cmath>

using namespace std;

int solution(int a, int b) {
    if (a % 2 == 1 && b % 2 == 1) {
        return a * a + b * b;
    }
    else if (a % 2 == 1 || b % 2 == 1) {
        return 2 * (a + b);
    }
    else return abs(a-b);
}