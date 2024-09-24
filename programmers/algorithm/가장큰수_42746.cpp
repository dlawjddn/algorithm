/**
 * @file 가장큰수_42746.cpp
 * @brief 프로그래머스 lv.2 가장 큰 수
 * @version 0.1
 * @date 2024-09-24
 * 
 * @copyright Copyright (c) 2024
 * 
 * 정렬 기준을 잘 잡아야 한다.. 
 * 이 생각으로 정렬을 할 생각을 전혀 못했네..
 * 
 */
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

bool compare(string& s1, string& s2) {
    return (s1 + s2) < (s2 + s1);
}

string solution(vector<int> numbers) {
    string answer = "";
    vector<string> strings;
    for(auto number : numbers) {
        strings.push_back(to_string(number));
    }
    sort(strings.rbegin(), strings.rend(), compare);
    for(auto str : strings) answer += str;
    return (answer[0] == '0') ? "0" : answer;
}