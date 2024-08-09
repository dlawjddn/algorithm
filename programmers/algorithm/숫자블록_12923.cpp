/**
 * @file 숫자블록_12923.cpp
 * @brief 프로그래머스 lv.2 숫자 블록
 * @version 0.1
 * @date 2024-08-09
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <string>
#include <vector>
#include <iostream>
using namespace std;

int find_divisor(long long origin) {
    int result = 1;
    for(long long div = 2; div * div <= origin; div++) {
        if (origin % div == 0) { // 나눠진다면
            result = div;
            if (origin / div <= 10000000) { // 조건에 부합한다면
                result = origin / div;
                break;
            }
            // 조건에 부합하지 않는다면 다음으로 큰 약수를 찾기
        }
    }
    return result;
}

vector<int> solution(long long begin, long long end) {
    vector<int> answer;
    for(long long i = begin; i<=end; i++) {
        if (i == 1) 
            answer.push_back(0);
        else
            answer.push_back(find_divisor(i));
    }
    return answer;
}