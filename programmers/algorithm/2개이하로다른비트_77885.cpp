/**
 * @file 2개이하로다른비트_77885.cpp
 * @brief 프로그래머스 lv.2 2개 이하로 다른 비트
 * @version 0.1
 * @date 2024-08-06
 * 
 * @copyright Copyright (c) 2024
 * 
 * 비트 연산에 대해 좀 더 알게 된 문제..
 * 이 코드는 지피티 코드이지만,, 확실하게 공부하고 넘어간다..
 * 비트 연산도 공부를 좀 해둬야겠다..!
 * 왕 신기하네..
 * 
 */
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

vector<long long> solution(vector<long long> numbers) {
    vector<long long> answer;
    for (auto number : numbers) {
        if (number % 2 == 0) { 
            // 짝수의 경우
            answer.push_back(number + 1);
        } else {
            // 홀수의 경우
            long long bit = 1;
            while (number & bit) {
                bit <<= 1;
            }
            answer.push_back(number + bit - (bit >> 1));
        }
    }
    return answer;
}