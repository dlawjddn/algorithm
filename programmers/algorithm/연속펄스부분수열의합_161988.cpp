/**
 * @file 연속펄스부분수열의합_161988.cpp
 * @brief 프로그래머스 lv.3 연속 펄스 부분 수열의 합
 * @version 0.1
 * @date 2024-08-20
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

long long solution(vector<int> sequence) {
    long long answer = 0;
    // 홀수번째가 -1인 경우
    long long sum_value = 0;
    for(int i=0; i<sequence.size(); i++) {
        int value = (i % 2 == 0) ? sequence[i] : -1 * sequence[i];
        sum_value += (long long)value;
        if (sum_value < 0) sum_value = 0;
        answer = max(answer, sum_value);
    }
    // 짝수번째가 -1인 경우
    sum_value = 0;
    for(int i=0; i<sequence.size(); i++) {
        int value = (i % 2 == 0) ? -1 * sequence[i] : sequence[i];
        sum_value += (long long)value;
        if (sum_value < 0) sum_value = 0;
        answer = max(answer, sum_value);
    }
    return answer;
}