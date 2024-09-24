/**
 * @file 정수내림차순으로배치하기_12933.cpp
 * @brief 프로그래머스 lv.1 정수 내림차순으로 배치하기
 * @version 0.1
 * @date 2024-09-24
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

long long solution(long long n) {
    string number = to_string(n);
    sort(number.rbegin(), number.rend());
    return stol(number);
}