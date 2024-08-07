/**
 * @file 메뉴리뉴얼_72411.cpp
 * @brief 프로그래머스 lv.2 카카오 2021 공채 메뉴 리뉴얼
 * @version 0.1
 * @date 2024-08-07
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <algorithm>

using namespace std;

vector<bool> visited;
unordered_map<string, int> maps;

void combination(int idx, string origin, string str, int goal) {
    if (str.size() == goal) {
        if (maps.find(str) == maps.end()) { // 존재하지 않는 경우
            maps.insert({str, 1});
        } else { // 이미 존재하는 경우
            maps[str] += 1;
        }
    }
    for(int i=idx; i<origin.size(); i++) {
        if (visited[i]) continue;
        visited[i] = true;
        str += origin[i];
        combination(i, origin, str, goal);
        str.pop_back();
        visited[i] = false;
    }
} 

vector<string> solution(vector<string> orders, vector<int> course) {
    vector<string> answer;
    for(auto &order : orders) sort(order.begin(), order.end());
    for(auto c : course) {
        maps = unordered_map<string, int>();
        for(auto order : orders) {
            visited = vector<bool>(order.size(), false);
            combination(0, order, "", c);
        }
        int max_cnt = 2;
        for(auto map : maps) {
            max_cnt = max(max_cnt, map.second);
        }
        for(auto map : maps) {
            if (map.second == max_cnt) answer.push_back(map.first);
        }
    }
    sort(answer.begin(), answer.end());
    return answer;
}