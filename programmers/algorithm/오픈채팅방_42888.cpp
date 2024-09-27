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
/**
 * @file 오픈채팅방_42888.cpp
 * @brief 프로그래머스 lv.2 2019 카카오 공채 오픈 채팅방
 * @version 0.1
 * @date 2024-09-27
 * 
 * @copyright Copyright (c) 2024
 * 
 * 이번에는 한번에 풀었지롱~
 * 
 */
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <unordered_map>

using namespace std;

struct Info {
    string action, userid, nickname;
};
unordered_map<string, string> user_name;

Info make_info(string action, string userid, string nickname) {
    Info info;
    info.action = action;
    info.userid = userid;
    info.nickname = nickname;
    return info;
}

vector<string> split(string origin) {
    vector<string> result;
    string token;
    istringstream token_stream(origin);
    while(getline(token_stream, token, ' ')) {
        result.push_back(token);
    }
    return result;
}

vector<string> solution(vector<string> record) {
    vector<string> answer;
    vector<Info> data;
    for(auto r : record) {
        vector<string> splited = split(r);
        string action = splited[0];
        string userid = splited[1];
        string nickname = "";
        if (splited[0] == "Enter" || splited[0] == "Change") {
            nickname = splited[2];
            user_name[userid] = nickname;
        }
        data.push_back(make_info(action, userid, nickname));
    }
    for(auto user : data) {
        if (user.action == "Change") continue;
        
        string str_answer = user_name[user.userid];
        if (user.action == "Enter") str_answer += "님이 들어왔습니다.";
        else str_answer += "님이 나갔습니다.";
        answer.push_back(str_answer);
    }
    return answer;
}