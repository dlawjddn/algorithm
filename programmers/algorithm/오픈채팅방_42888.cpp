/**
 * @file 오픈채팅방_42888.cpp
 * @brief 프로그래머스 lv.2 2019 카카오 신입공채 오픈채팅방
 * @version 0.1
 * @date 2024-08-06
 * 
 * @copyright Copyright (c) 2024
 * 
 * 문제를 잘 읽자...
 * 1. Leave의 경우에는 split의 결과가 2개 밖에 존재하지 않는다!
 * 2. unordered_map 이나 map은 키값의 중복을 허용하지 않는다 -> 진짜 중요함
 * 
 */
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <sstream>

using namespace std;

unordered_map<string, string> users; // 유저아이디 - 닉네임

vector<string> split(string origin, char delimeter) {
    vector<string> result;
    string token;
    istringstream token_stream(origin);
    while(getline(token_stream, token, delimeter))
        result.push_back(token);
    return result;
}

vector<string> solution(vector<string> record) {
    vector<string> answer;
    vector<pair<string, string> > temp;
    for(auto r : record) {
        vector<string> splited = split(r, ' ');
        string action = splited[0];
        string userid = splited[1];
        temp.push_back({action, userid});
        if (action == "Enter" || action == "Change") { // 채팅방에 들어온 경우 || 변경하는 경우
            string nickname = splited[2];
            if (users.find(userid) != users.end()) { // 이미 들어왔던 경우
                users[userid] = nickname;
            } else { // 첫 방문인 경우
                users.insert({userid, nickname});
            }
        }
    }
    for(auto info : temp) {
        auto[action, userid]  = info;
        if (action == "Enter") {
            answer.push_back(users[userid] + "님이 들어왔습니다.");
        }
        if (action == "Leave") {
            answer.push_back(users[userid] + "님이 나갔습니다.");
        }
    }
    return answer;
}