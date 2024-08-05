/**
 * @file 3차_압축_17684.cpp
 * @brief 프로그래머스 lv.2 2018 카카오 공채 3차 압축
 * @version 0.1
 * @date 2024-08-05
 * 
 * @copyright Copyright (c) 2024
 * 
 * 문제 이해가 안 가서.. 문제 설명을 읽고 풀었는데.. 너무 허무하게 풀려버림..
 * 너무 찝찝한데..
 * 
 */
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

unordered_map<string, int> dict;

void init() {
    for(int i=1; i<=26; i++) {
        dict.insert({to_string(i - 1 + 'A'), i});
    }
}

vector<int> solution(string msg) {
    vector<int> answer;
    string str = "";
    int idx = 0;
    int dict_idx = 27;
    init();
    while(idx < msg.size()) {
        if (idx == msg.size() - 1) {
            answer.push_back(dict[to_string(msg[idx++])]);
            cout<<dict[to_string(msg[idx++])];
            break;
        } else {
            string before = "";
            string now = to_string(msg[idx]);
            while(dict.find(now) != dict.end()) {
                before = now;
                now += msg[++idx];
            }
            dict.insert({now, dict_idx++});
            cout<<dict[before]<<" ";
            answer.push_back(dict[before]);
        }
    }
    return answer;
}