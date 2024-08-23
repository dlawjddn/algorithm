/**
 * @file 광고삽입_72414.cpp
 * @brief 2021 프로그래머스 lv.3 광고삽입
 * @version 0.1
 * @date 2024-08-22
 * 
 * @copyright Copyright (c) 2024
 * 
 * 와.. 누적합을 이렇게 하는구나.. 하나 배워간다.. 꼭 다시 풀도록 하자
 * 
 */
#include <string>    
#include <vector>    
#include <iostream>  
#include <algorithm> 
#include <cstdio>    
#include <sstream>

using namespace std;

vector<string> split(string origin, char delimeter) {
    vector<string> result;
    string token;
    istringstream token_stream(origin);
    while (getline(token_stream, token, delimeter)) {
        result.push_back(token);
    }
    return result;
}

int convert_number(string time) {
    vector<string> splited = split(time, ':');
    return stoi(splited[0]) * 3600 + stoi(splited[1]) * 60 + stoi(splited[2]);
}

string convert_to_time(int time) {
    int h = time / 3600;
    int m = (time % 3600) / 60;
    int s = time % 60;
    char buffer[9];
    sprintf(buffer, "%02d:%02d:%02d", h, m, s);
    return string(buffer);
}

string solution(string play_time, string adv_time, vector<string> logs) {
    int play = convert_number(play_time);
    int ad = convert_number(adv_time);
    vector<int> total_time(play + 1, 0);

    for (auto log : logs) {
        vector<string> times = split(log, '-');
        int start = convert_number(times[0]);
        int end = convert_number(times[1]);
        total_time[start]++;
        total_time[end]--;
    }

    // 시청자 누적 시간을 계산합니다.
    for (int i = 1; i <= play; i++) {
        total_time[i] += total_time[i - 1];
    }

    // 광고 시작 시간을 0초부터 play - adv 까지 시도해봅니다.
    long long max_time = 0, current_time = 0;
    int max_start_time = 0;

    for (int i = 0; i < ad; i++) {
        current_time += total_time[i];
    }
    max_time = current_time;

    for (int i = ad; i < play; i++) {
        current_time = current_time + total_time[i] - total_time[i - ad];
        if (current_time > max_time) {
            max_time = current_time;
            max_start_time = i - ad + 1;
        }
    }

    return convert_to_time(max_start_time);
}

/**
 * @file 광고삽입_72414.cpp
 * @brief 프로그래머스 lv.3 2021 광고삽입
 * @version 0.1
 * @date 2024-08-23
 * 
 * @copyright Copyright (c) 2024
 * 
 * 구간합 & 구간의 양 끝 고려하는게 중요하고
 * 각 값이 int 범위를 넘어가는지 안 넘어가지는지 파악하는게 중요했음
 * 
 */
#include <string>
#include <vector>
#include <iostream>
#include <sstream>

using namespace std;

vector<string> split(string origin, char delimeter) {
    vector<string> result;
    string token;
    istringstream token_stream(origin);
    while(getline(token_stream, token, delimeter)) {
        result.push_back(token);
    }
    return result;
}

int convert_to_number(string time) {
    vector<string> splited = split(time, ':');
    return stoi(splited[0]) * 3600 + stoi(splited[1]) * 60 + stoi(splited[2]);
}

string convert_to_string(int num) {
    string result = "";
    string hour = to_string(num / 3600);
    if (hour.size() < 2) result += '0';
    result += hour;
    num %= 3600;
    result += ':';
    string minute = to_string(num / 60);
    if (minute.size() < 2) result += '0';
    result += minute;
    num %= 60;
    result += ':';
    string second = to_string(num);
    if (second.size() < 2) result += '0';
    result += second;
    return result;
}

string solution(string play_time, string adv_time, vector<string> logs) {
    string answer = "";
    int play = convert_to_number(play_time);
    int ad = convert_to_number(adv_time);
    vector<int> watching_people(play + 1, 0);
    // 보는 사람의 시작 시간과 종료 시간에 변화량 체크하기 -> 구간을 파악하기 위해서
    for(auto log : logs) {
        vector<string> splited = split(log, '-');
        watching_people[convert_to_number(splited[0])]++;
        watching_people[convert_to_number(splited[1])]--;
    }
    // 각 시간에 보는 사람 수 세기
    for(int i=1; i<watching_people.size(); i++) {
        watching_people[i] += watching_people[i-1];
    }
    
    long long current_people = 0, max_people = 0, max_start_time = 0;
    // 시간의 최대값이 99:59:60 -> 대충 400만이거든
    // 근데 logs(시청자 수)가 30만임
    // 근데 이게 전 구간에 대해서 30만명이 다 보면
    // 400만 * 30만인데 -> 인트 범위 넘어가네
    // 시작하자마자 광고 재생하는 경우
    for(int i=0; i<ad; i++) {
        current_people += watching_people[i];
    }
    max_people = current_people;
    // 끝나는 시간을 기준으로 play 까지
    for(int i=ad; i<play; i++) {
        // ad + n ~ ad + ad + n까지의 누적 시청자 구하기
        current_people = current_people + watching_people[i] - watching_people[i-ad];
        if (max_people < current_people) {
            max_people = current_people;
            max_start_time = i - ad + 1;
        }
    }
    return convert_to_string(max_start_time);
}