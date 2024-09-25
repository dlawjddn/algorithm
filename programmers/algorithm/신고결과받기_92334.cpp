/**
 * @file 신고결과받기_92334.cpp
 * @brief 프로그래머스 lv.0 2022 카카오 공채 신고 결과 받기
 * @version 0.1
 * @date 2024-09-25
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <unordered_map>
#include <set>

using namespace std;

unordered_map<string, int> name_to_idx;
unordered_map<string, set<string> > ban_report;

pair<string, string> split(string origin) {
    vector<string> result;
    string token;
    istringstream token_stream(origin);
    while(getline(token_stream, token, ' ')) {
        result.push_back(token);
    }
    return {result[0], result[1]};
}

vector<int> solution(vector<string> id_list, vector<string> report, int k) {
    vector<int> answer(id_list.size(), 0);
    // string -> idx 적용
    for(int i=0; i<id_list.size(); i++) {
        string user = id_list[i];
        name_to_idx[user] = i;
    }
    // report 파악
    for(auto submit : report) {
        auto[sender, receiver] = split(submit);
        ban_report[receiver].insert(sender);
    }
    // report 결과 확인, 메일 전송 여부 파악
    for(int i=0; i<id_list.size(); i++) {
        string user = id_list[i];
        if (ban_report[user].size() >= k) { // user = 정지되는 사용자
            for(auto reporter : ban_report[user]) {
                answer[name_to_idx[reporter]]++;
            }
        }
    }
    return answer;
}