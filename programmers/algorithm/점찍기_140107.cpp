/**
 * @file 점찍기_140107.cpp
 * @brief 프로그래머스 lv.2 점 찍기
 * @version 0.1
 * @date 2024-08-12
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <string>
#include <vector>
#include <cmath>

using namespace std;

long long solution(int k, int d) {
    long long increase = (long long) k;
    long long limit = (long long) d;
    long long answer = 0;
    for (long long y = 0; y <= limit; y += increase) {
        long long x_max = (long long)sqrt(limit * limit - y * y);
        answer += (x_max / increase) + 1;
    }
    return answer;
}