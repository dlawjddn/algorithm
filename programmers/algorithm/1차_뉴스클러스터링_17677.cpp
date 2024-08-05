/**
 * @file 1차_뉴스클러스터링_17677.cpp
 * @brief 프로그래머스 lv.2 2018 카카오 블라인드 1차_뉴스클러스터링
 * @version 0.1
 * @date 2024-08-05
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <string>
#include <unordered_map>
#include <iostream>

using namespace std;

unordered_map<string, int> both_map;
unordered_map<string, int> or_map;
unordered_map<string, int> map1;
unordered_map<string, int> map2;

string lower_case(string origin) {
    string new_string = "";
    for(auto c : origin) {
        if (c >= 'A' && c <= 'Z') {
            new_string += (c  - 'A' + 'a');
            continue;
        }
        new_string += c;
    }
    return new_string;
}

bool check_alpha(char a, char b) {
    if (a >= 'a' && a <= 'z' && b >= 'a' && b <= 'z') return true;
    return false;
}

int solution(string str1, string str2) {
    int answer = 0;
    str1 = lower_case(str1);
    str2 = lower_case(str2);
    for(int i=1; i<str1.size(); i++) {
        if (!check_alpha(str1[i-1], str1[i])) continue;
        string part = "";
        part += str1[i-1];
        part += str1[i];
        if (map1.find(part) != map1.end()) {
            map1[part] += 1;
        } else map1.insert({part, 1});
    }
    for(int i=1; i<str2.size(); i++) {
        if (!check_alpha(str2[i-1], str2[i])) continue;
        string part = "";
        part += str2[i-1];
        part += str2[i];
        if (map2.find(part) != map2.end()) {
            map2[part] += 1;
        } else map2.insert({part, 1});
    }
    for(auto info : map1) {
        string part1 = info.first;
        int cnt1 = info.second;
        if (map2.find(part1) != map2.end()) { // map1에 존재하는게 map2에도 존재하는 경우
            // 1. 교집합의 경우에는 cnt 중 작은 값
            // 2. 합집합의 경우에는 cnt 중 큰 값
            int cnt2 = map2[part1];
            both_map.insert({part1, min(cnt1, cnt2)});
            or_map.insert({part1, max(cnt1, cnt2)});
        } 
        else { // map1에 존재하는게 map2에 존재하지 않는 경우 -> 합집합에만 추가
            or_map.insert({part1, cnt1});
        }
    }
    for(auto info : map2) {
        string part2 = info.first;
        int cnt2 = info.second;
        if (map1.find(part2) == map1.end())
            or_map.insert({part2, cnt2});
    }
    int or_cnt = 0;
    for(auto info : or_map) {
        or_cnt += info.second;
    }
    int both_cnt = 0;
    for(auto info : both_map) {
        both_cnt += info.second;
    }
    if (or_cnt == 0 && both_cnt == 0) return 65536;
    else {
        double percent = (double) both_cnt / (double) or_cnt;
        answer = percent * 65536.0;
    }
    
    return answer;
}