/**
 * @file 큰수만들기_42883.cpp
 * @brief 프로그래머스 lv.2 큰 수 만들기
 * @version 0.1
 * @date 2024-08-07
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string solution(string number, int k) {
    string answer = "";
    int length = number.size() - k;
    int left = 0, right = number.size() - length;
    for (int i = 0; i < length; i++) {
        char max_digit = '0';
        for (int j = left; j <= right; j++) {
            if (number[j] > max_digit) {
                max_digit = number[j];
                left = j + 1;
            }
        }
        answer += max_digit;
        right++;
    }
    return answer;
}
