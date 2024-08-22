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
