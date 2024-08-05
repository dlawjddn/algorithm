/**
 * @file 3차_n진수게임_17687.cpp
 * @brief 프로그래머스 lv.2 2018 카카오 공채 3차 n진수게임
 * @version 0.1
 * @date 2024-08-05
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

char over_ten(int num) {
    if (num == 10) return 'A';
    else if (num == 11) return 'B';
    else if (num == 12) return 'C';
    else if (num == 13) return 'D';
    else if (num == 14) return 'E';
    return 'F';
}

string change_digit(int number, int n) {
    string result = "";
    if (number == 0) return "0";
    while(number > 0) {
        int num = (number % n);
        if (num > 9 && n > 10)
            result += over_ten(num);
        else 
            result += to_string(num);
        number /= n;
    }
    reverse(result.begin(), result.end());
    return result;
}

string solution(int n, int t, int m, int p) {
    string answer = "";
    string total = "";
    int number = 0;
    while(1) {
        total += change_digit(number++, n);
        if (total.size() >= t * m) break;
    }
    int myturn = p - 1, cnt = 0;
    while(cnt < t) {
        answer += total[myturn];
        myturn += m;
        cnt++;
    }
    return answer;
}