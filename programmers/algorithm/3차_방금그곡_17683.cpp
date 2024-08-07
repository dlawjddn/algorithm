/**
 * @file 3차_방금그곡_17683.cpp
 * @brief 프로그래머스 lv.2 2018 카카오 공채 3차 방금 그 곡
 * @version 0.1
 * @date 2024-08-07
 * 
 * @copyright Copyright (c) 2024
 * 
 * 배열 순회시, 2개 이상의 요소를 조회할 때는 반드시 배열 범위를 나가는지 여부를 파악해서 하자..
 * 이 문제에서 아주 좋은 예시가 있다..!!!!
 * 
 */
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

struct Info {
    int length;
    string title;
    string melody;
    
    bool operator<(Info other) const {
        return length > other.length;
    }
};
vector<Info> infos;

vector<string> split(string origin, char delimeter) {
    vector<string> result;
    string token;
    istringstream token_stream(origin);
    while(getline(token_stream, token, delimeter)) {
        result.push_back(token);
    }
    return result;
}

string change_str(string origin) {
    string result = "";
    for(int i = 0; i < origin.size(); i++) {
        char char_first = origin[i];
        if (i + 1 < origin.size() && origin[i + 1] == '#') {
            result += char_first - 'A' + 'a';
            i++;
        } else {
            result += char_first;
        }
    }
    return result;
}

int change_minute(string hour_str, string minute_str) {
    int hour = stoi(hour_str);
    int minute = stoi(minute_str);
    return hour * 60 + minute;
}

int cal_length(string start, string end) {
    vector<string> start_time = split(start, ':');
    vector<string> end_time = split(end, ':');
    int start_point = change_minute(start_time[0], start_time[1]);
    int end_point = change_minute(end_time[0], end_time[1]);
    return end_point - start_point;
}

string make_melody(int length, string origin) {
    string result = "";
    for(int i = 0; i < length; i++) {
        result += origin[i % origin.size()];
    }
    return result;
}

Info make_info(string& musicinfo) {
    vector<string> splited = split(musicinfo, ',');
    int len = cal_length(splited[0], splited[1]);
    Info info;
    info.length = len;
    info.title = splited[2];
    info.melody = make_melody(len, change_str(splited[3]));
    return info;
}

string solution(string m, vector<string> musicinfos) {
    string answer = "";
    for(auto musicinfo : musicinfos) {
        infos.push_back(make_info(musicinfo));
    }
    sort(infos.begin(), infos.end());
    m = change_str(m);
    
    for(auto info : infos) {
        if (info.melody.find(m) != string::npos) {
            return info.title;
        }
    }
    return "(None)";
}
