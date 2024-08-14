/**
 * @file 후보키_42890.cpp
 * @brief 프로그래머스 lv.2 2019 카카오 공체 후보키
 * @version 0.1
 * @date 2024-08-14
 * 
 * @copyright Copyright (c) 2024
 * 
 * 최소성에 대한 판단 기준을 이해 하지 못해서.. 아쉽다 ㅅㅂ..
 * 
 */
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <set>

using namespace std;

int row_size = 0, col_size = 0;
vector<string> answer;

// 최소성: 후보키의 후보들의 조합이 기존에 생성된 후보키 + 특정 릴레이션인 경우 최소성을 만족하지 못함
// 결국, 현재 후보키의 후보가 기존 후보키들 중 포함관계인 경우는 최소성을 만족하지 않기 때문에
// 현재 탐색 중인 후보키의 후보가 후보키 중 하나라도 포함관계인지 파악하면 된다.

bool is_minimal(const string& chosen) {
    for (const string& a : answer) {
        int cnt = 0;
        for (char c : a) {
            if (chosen.find(c) != string::npos) {
                cnt++;
            }
        }
        if (cnt == a.size()) return false;
    }
    return true;
}

void check_cols(vector<vector<string>>& relation, string chosen) {
    set<string> result;
    for (const auto& row : relation) {
        string data = "";
        for (char c : chosen) {
            int idx = c - '0';
            data += row[idx];
        }
        result.insert(data);
    }
    if (result.size() == row_size && is_minimal(chosen)) {
        answer.push_back(chosen);
    }
}

void choose_col(vector<vector<string>>& relation, int idx, int total_cnt, string chosen) {
    if (chosen.size() == total_cnt) {
        check_cols(relation, chosen);
        return;
    }
    for (int i = idx; i < col_size; i++) {
        choose_col(relation, i + 1, total_cnt, chosen + to_string(i));
    }
}

int solution(vector<vector<string>> relation) {
    row_size = relation.size();
    col_size = relation[0].size();
    for (int i = 1; i <= col_size; i++) {
        choose_col(relation, 0, i, "");
    }
    //for (auto a : answer) cout << a << "\n";
    return answer.size();
}
