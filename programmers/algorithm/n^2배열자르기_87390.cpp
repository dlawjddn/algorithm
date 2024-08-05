/**
 * @file n^2배열자르기_87390.cpp
 * @brief 프로그래머스 lv.2 n^2 배열자르기
 * @version 0.1
 * @date 2024-08-05
 * 
 * @copyright Copyright (c) 2024
 * 
 * 아니 그래 이 생각을 왜 못했지.. 짜증나네..
 * 
 */
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

vector<int> solution(int n, long long left, long long right) {
    vector<int> answer;
    for(long long i = left; i<=right; i++) {
        answer.push_back(max(i/n, i%n)+1);
    }
    return answer;
}