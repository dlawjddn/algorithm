/**
 * @file 1차_추석트래픽_17676.cpp
 * @brief 프로그래머스 lv.3 2018 카카오 공채 1차
 * @version 0.1
 * @date 2024-09-23
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <string>
#include <vector>
#include <iostream>
#include <sstream>

using namespace std;

vector<int> start_at;
vector<int> end_at;

vector<string> split(string origin, char delimeter) {
    vector<string> result;
    string token;
    istringstream token_stream(origin);
    while (getline(token_stream, token, delimeter)) {
        result.push_back(token);
    }
    return result;
}

int convert_mili(string second) {
    string zero_base = "0.";
    zero_base += second;
    double mili = stod(zero_base);
    return (int)(mili * 1000); // 수정: 소수를 밀리초로 변환
}

int convert_int(string time, string second) {
    int result = 0;
    vector<string> splited = split(time, ':');
    result += stoi(splited[0]) * 1000 * 60 * 60;
    result += stoi(splited[1]) * 1000 * 60;
    result += stoi(splited[2]) * 1000;
    result += convert_mili(second);
    return result; // 수정: 반환값 추가
}

int convert_process_time(string process) {
    process.pop_back();
    double second = stod(process);
    return (int)(second * 1000); // 수정: 초를 밀리초로 변환
}

int solution(vector<string> lines) {
    int answer = 0;
    for (int i = 0; i < lines.size(); i++) {
        vector<string> splited = split(lines[i], ' ');
        vector<string> detail_time = split(splited[1], '.');
        int end_time = convert_int(detail_time[0], detail_time[1]);
        int process_time = convert_process_time(splited[2]);
        int start_time = end_time - process_time + 1;
        start_at.push_back(start_time);
        end_at.push_back(end_time);
    }
    
    // 각 로그의 끝나는 시간과 시작 시간을 기준으로 1초 구간의 최대 처리량 계산
    for (int i = 0; i < start_at.size(); i++) {
        // 끝나는 시간을 기준으로 1초 구간
        int end_window_start = end_at[i];
        int end_window_end = end_window_start + 999;
        int count = 0;

        for (int j = 0; j < start_at.size(); j++) {
            // 현재 로그가 구간 안에 있는지 확인
            if (!(start_at[j] > end_window_end || end_at[j] < end_window_start)) {
                count++;
            }
        }

        answer = max(answer, count);

        // 시작 시간을 기준으로 1초 구간
        int start_window_start = start_at[i];
        int start_window_end = start_window_start + 999;
        count = 0;

        for (int j = 0; j < start_at.size(); j++) {
            // 현재 로그가 구간 안에 있는지 확인
            if (!(start_at[j] > start_window_end || end_at[j] < start_window_start)) {
                count++;
            }
        }

        answer = max(answer, count);
    }
    return answer;
}