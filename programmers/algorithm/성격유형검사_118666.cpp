/**
 * @file 성격유형검사_118666.cpp
 * @brief 프로그래머스 lv.1 2022 카카오 인턴십 성격 유형 검사하기
 * @version 0.1
 * @date 2024-08-21
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <string>
#include <vector>
#include <cmath>
#include <unordered_map>

using namespace std;

unordered_map<char, int> map;

string solve() {
    string result = "";
    int r_cnt = map['R'];
    int t_cnt = map['T'];
    if (r_cnt < t_cnt) result += 'T';
    else result += 'R';
    
    int c_cnt = map['C'];
    int f_cnt = map['F'];
    if (c_cnt < f_cnt) result += 'F';
    else result += 'C';
    
    int j_cnt = map['J'];
    int m_cnt = map['M'];
    if (j_cnt < m_cnt) result += 'M';
    else result += 'J';
    
    int a_cnt = map['A'];
    int n_cnt = map['N'];
    if (a_cnt < n_cnt) result += 'N';
    else result += 'A';
    
    return result;
}

string solution(vector<string> survey, vector<int> choices) {
    for(int i=0; i<survey.size(); i++) {
        int score = choices[i] - 4;
        if (score == 0) continue;
        else if (score < 0) {
            map[survey[i][0]] += abs(score);
        } else map[survey[i][1]] += abs(score);
    }
    return solve();
}