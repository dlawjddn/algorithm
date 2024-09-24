/**
 * @file 문자열내맘대로정렬하기_12915.cpp
 * @brief 프로그래머스 lv.1 문자열 내 맘대로 정렬하기
 * @version 0.1
 * @date 2024-09-24
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int standard;

struct Compare{
    bool operator()(string& s1, string& s2) {
        if (s1[standard] == s2[standard]) {
            return s1 < s2;
        }
        return s1[standard] < s2[standard];
    }
};

vector<string> solution(vector<string> strings, int n) {
    vector<string> answer;
    standard = n;
    sort(strings.begin(), strings.end(), Compare());
    return strings;
}