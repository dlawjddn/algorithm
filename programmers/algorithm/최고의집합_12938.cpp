/**
 * @file 최고의집합_12938.cpp
 * @brief 프로그래머스 lv.3 최고의 집합
 * @version 0.1
 * @date 2024-08-17
 * 
 * @copyright Copyright (c) 2024
 * 
 * 흠.. 기존에 풀었던건데 초기화를 늦게 해서 기존 코드를 읽어버렸다.. 다시 풀어보도록 하자
 * 
 */
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

vector<int> solution(int n, int s) {
    vector<int> answer;
    if (n > s) return {-1};
    while(n) {
        answer.push_back(s/n);
        s -= s/n;
        n--;
        if (n == 0) break;
    }
    return answer;
}