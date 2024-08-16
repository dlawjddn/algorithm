/**
 * @file 가장긴팰린드롬_12904.cpp
 * @brief 프로그래머스 lv.2 가장 긴 팰린드롬
 * @version 0.1
 * @date 2024-08-17
 * 
 * @copyright Copyright (c) 2024
 * 
 * 짝수 길이의 팰린드롬을 생각하지 못했다..
 */
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

bool check_outside(int left, int right, string s) {
    return left < 0 || right >= s.size();
}

int solution(string s){
    int answer = 0;
    // 홀수 길이의 팰린드롬
    for(int i=0; i<s.size(); i++) {
        int len = 0, left = i-1, right = i+1;
        while(true) {
            if (check_outside(left, right, s)) break;
            if (s[left] == s[right]) {
                len++;
                left--;
                right++;
            } else break;
        }
        answer = max(answer, len * 2 + 1);
    }
    // 짝수 길이의 팰린드롬
    for(int i=0; i<s.size(); i++) {
        int len = 0, left = i, right = i+1;
        while(true) {
            if (check_outside(left, right, s)) break;
            if (s[left] == s[right]) {
                len++;
                left--;
                right++;
            } else break;
        }
        answer = max(answer, len * 2);
    }
    return answer;
}