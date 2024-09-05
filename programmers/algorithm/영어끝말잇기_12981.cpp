/**
 * @file 영어끝말잇기_12981.cpp
 * @brief 프로그래머스 lv.2 영어 끝말 잇기
 * @version 0.1
 * @date 2024-09-05
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <string>
#include <vector>
#include <set>

using namespace std;

set<string> check;

vector<int> solution(int n, vector<string> words) {
    vector<int> answer;
    check.insert(words[0]);
    for(int i=1; i<words.size(); i++) {
        string before = words[i-1];
        string now = words[i];
        if (before[before.size() - 1] != now[0] || check.find(now) != check.end()) {
            int turn = ((i + 1) % n == 0) ? (i + 1) / n : (i + 1) / n + 1;
            return {(i % n) + 1, turn};
        }
        check.insert(words[i]);
    }
    return {0, 0};
}