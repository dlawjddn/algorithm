/**
 * @file 주차요금계산_92341.cpp
 * @brief 프로그래머스 lv.2 카카오 2022 공채 주차요금계산
 * @version 0.1
 * @date 2024-08-05
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <iostream>
#include <algorithm>

using namespace std;

unordered_map<string, pair<int, int> > infos;

vector<string> split(string origin, char delimeter) {
    vector<string> result;
    string token;
    istringstream token_stream(origin);
    while(getline(token_stream, token, delimeter)) {
        result.push_back(token);
    }
    return result;
}

int total_minutes(string time) {
    vector<string> info = split(time, ':');
    int hour = stoi(info[0]);
    int minute = stoi(info[1]);
    return hour * 60 + minute;
}

vector<int> solution(vector<int> fees, vector<string> records) {
    vector<int> answer;
    unordered_map<string, int> result;
    for(auto record : records) {
        vector<string> info = split(record, ' ');
        if (info[2] == "IN") {
            infos.insert({info[1], {total_minutes(info[0]), total_minutes("23:59")}});
        } else {
            infos[info[1]].second = total_minutes(info[0]);
            // 여기서 매칭된 차에 대해서 누적 시간 계산
            string car_number = info[1];
            int total_time = infos[info[1]].second - infos[info[1]].first;
            if (result.find(car_number) != result.end()) {
                result[car_number] += total_time;
            } else {
                result[car_number] = total_time;
            }
            infos.erase(car_number);
        }
    }
    // 출차 기록이 없는 차에 대해서 다시 계산
    for(auto info : infos) {
        string car_number = info.first;
        int total_time = info.second.second - info.second.first;
        if (result.find(car_number) != result.end()) {
            result[car_number] += total_time;
        } else {
            result[car_number] = total_time;
        }
    }
    vector<pair<string, int> > sorted_result;
    // 누적 시간에 대한 총 가격 계산
    for(auto r : result) {
        string car_number = r.first;
        int total_time = r.second;
        int total_price = fees[1];
        if (total_time > fees[0]) { // 추가 요금 지불 필요
            int additional_time = total_time - fees[0];
            if (additional_time % fees[2] == 0) {
                total_price += (additional_time / fees[2]) * fees[3];
            } else {
                total_price += (additional_time / fees[2] + 1) * fees[3];
            }
        }
        sorted_result.push_back({car_number, total_price});
    }
    // 차번호 오름차순으로 정렬
    sort(sorted_result.begin(), sorted_result.end());
    for(auto result : sorted_result) {
        answer.push_back(result.second);
    }
    
    return answer;
}

/**
 * @file 주차요금계산_92341.cpp
 * @brief 프로그래머스 lv.2 카카오 2022 공채 주차요금계산
 * @version 0.1
 * @date 2024-09-05
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include <set>

using namespace std;

unordered_map<string, int> total_time;
unordered_map<string, pair<int, int> > in_out;

vector<string> split(string origin, char delimeter) {
    vector<string> result;
    string token;
    istringstream token_stream(origin);
    while(getline(token_stream, token, delimeter)) {
        result.push_back(token);
    }
    return result;
}

int change_to_int(string time) {
    vector<string> splited = split(time, ':');
    int hour = stoi(splited[0]);
    int minute = stoi(splited[1]);
    return hour * 60 + minute;
}

int cal_fee(vector<int>& fees, int total_minute) {
    int basic_minute = fees[0];
    int basic_fee = fees[1];
    int over_minute = fees[2];
    int over_fee = fees[3];
    if (total_minute <= basic_minute) {
        return basic_fee;
    }
    else {
        int over_time = total_minute - basic_minute;
        if (over_time % over_minute == 0) 
            return basic_fee + over_fee * (over_time / over_minute);
        else return basic_fee + over_fee * ((over_time / over_minute) + 1);
    }
}

vector<int> solution(vector<int> fees, vector<string> records) {
    vector<int> answer;
    for(auto record : records) {
        vector<string> info = split(record, ' ');
        if (info[2] == "IN") {
            in_out[info[1]] = {change_to_int(info[0]), 23 * 60 + 59};
        }
        else {
            int come_time = in_out[info[1]].first;
            int out_time = change_to_int(info[0]);
            total_time[info[1]] += (out_time - come_time);
            in_out.erase(info[1]);
        }
    }
    for(auto record : in_out) {
        string car_id = record.first;
        pair<int, int> info = record.second;
        total_time[car_id] += (info.second - info.first);
    }
    set<pair<string, int> > result(total_time.begin(), total_time.end());
    for(auto r : result) {
        answer.push_back(cal_fee(fees, r.second));
    }
    return answer;
}