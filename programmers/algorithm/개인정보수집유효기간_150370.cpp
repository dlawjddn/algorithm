/**
 * @file 개인정보수집유효기간_150370.cpp
 * @brief 프로그래머스 lv.1 2023 카카오 공채 개인정보 수집 유효기간
 * @version 0.1
 * @date 2024-09-28
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <unordered_map>

using namespace std;

struct Date {
    int year, month, day;
};

unordered_map<string, int> limit;

void print_date(Date date) {
    cout << date.year << " " << date.month << " " << date.day << "\n";
}

Date make_date(int year, int month, int day) {
    Date date;
    date.year = year;
    date.month = month;
    date.day = day;
    return date;
}

Date cal_end_date(Date start, int add_month) {
    int year = start.year;
    int month = start.month + add_month;
    int day = start.day - 1;
    if (day == 0) {
        day = 28;
        month -= 1;
    }
    if (month <= 0) {
        month += 12;
        year -= 1;
    }
    year += (month - 1) / 12;
    month = (month - 1) % 12 + 1;
    return make_date(year, month, day);
}

bool compare_date(Date now, Date end_date) {
    // True: 보관 가능
    // False : 폐기
    if (now.year == end_date.year) {
        if (now.month == end_date.month) {
            return now.day > end_date.day;
        }
        return now.month > end_date.month;
    }
    return now.year > end_date.year;
}

vector<string> split(string origin, char delimeter) {
    vector<string> result;
    string token;
    istringstream token_stream(origin);
    while (getline(token_stream, token, delimeter)) {
        result.push_back(token);
    }
    return result;
}

void init_limit(vector<string>& terms) {
    for (auto term : terms) {
        vector<string> splited = split(term, ' ');
        limit[splited[0]] = stoi(splited[1]);
    }
}

vector<int> solution(string today, vector<string> terms, vector<string> privacies) {
    vector<int> answer;
    init_limit(terms);
    vector<string> this_day = split(today, '.');
    Date now = make_date(stoi(this_day[0]), stoi(this_day[1]), stoi(this_day[2]));
    print_date(now);
    for (int i = 0; i < privacies.size(); i++) {
        vector<string> data = split(privacies[i], ' ');
        vector<string> str_start_date = split(data[0], '.');
        Date start = make_date(stoi(str_start_date[0]), stoi(str_start_date[1]), stoi(str_start_date[2]));
        Date end = cal_end_date(start, limit[data[1]]);
        if (compare_date(now, end)) answer.push_back(i + 1);
    }
    return answer;
}
