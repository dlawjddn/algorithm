/**
 * @file 1차_셔틀버스_17678.cpp
 * @brief 프로그래머스 lv.3 [1차] 셔틀버스
 * @version 0.1
 * @date 2024-06-24
 * 
 * @copyright Copyright (c) 2024
 * 
 * 간단한 구현인데.. 더 고민해보자..
 * 
 */
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

string cal_time(string time, int min) {
    string result = "";
    int hour = stoi(time.substr(0, 2));
    int minute = stoi(time.substr(3, 2));
    int total_time = hour * 60 + minute + min;
    int h = total_time / 60;
    int m = total_time % 60;
    if (h < 10) {
        result += "0";
    }
    result += to_string(h);
    result += ":";
    if (m < 10) {
        result += "0";
    }
    result += to_string(m);
    return result;
}

string solution(int n, int t, int m, vector<string> timetable) {
    string answer = "";
    sort(timetable.begin(), timetable.end());
    string bus_time = "09:00";
    int timetable_idx = 0;
    for(int i=0; i<n; i++) {
        int cnt = 0;
        string current_bus_time = cal_time(bus_time, i * t);
        string before = current_bus_time;
        for(int j = timetable_idx; j<timetable.size(); j++) {
            // 탈 수 있는 경우
            if (current_bus_time >= timetable[j]) {
                cnt += 1;
                before = timetable[j];
                timetable_idx += 1;
                if (cnt == m) break;
            }
            // 탈 수 없는 경우
            else break;
        }
        // 마지막 버스인 경우
        if (i == n - 1) {
            // 마지막에 탈 수 있는 경우
            if (cnt < m)
                return current_bus_time;
            else 
                return cal_time(before, -1);
        }
        
    }
}
/**
 * @file 1차_셔틀버스_17678.cpp
 * @brief 프로그래머스 lv.3 2018 카카오 공채 1차 셔틀버스
 * @version 0.1
 * @date 2024-08-20
 * 
 * @copyright Copyright (c) 2024
 * 
 * 아 씨발 너무 어렵게 생각했다.. 아 짜증난다..
 * 
 */
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

priority_queue<int, vector<int>, greater<int> > pq;

int convert_time(string str_time) {
    int hour = stoi(str_time.substr(0, 2));
    int minute = stoi(str_time.substr(3));
    
    return hour * 60 + minute;
}

string convert_string(int time) {
    string result = "";
    int hour = time / 60;
    int minute = time % 60;
    if (hour < 10) result += '0';
    result += to_string(hour);
    result += ':';
    if (minute < 10) result += '0';
    result += to_string(minute);
    return result;
}

string solution(int n, int t, int m, vector<string> timetable) {
    string answer = "";
    for(auto time : timetable) pq.push(convert_time(time));
    int bus_time = 540;
    int last_people = 0;
    for(int i=0; i<n; i++) {
        int cnt = 0;
        while(!pq.empty() && pq.top() <= bus_time && cnt < m) {
            last_people = pq.top(); pq.pop();
            cnt++;
        }
        if (i == n-1) {
            if (cnt < m) answer = convert_string(bus_time);
            else answer = answer = convert_string(last_people - 1);
        }
        bus_time += t;
    }
    return answer;
}