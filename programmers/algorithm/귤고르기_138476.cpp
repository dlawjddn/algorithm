/**
 * @file 귤고르기_138476.cpp
 * @brief 프로그래머스 lv.2 귤 고르기
 * @version 0.1
 * @date 2024-10-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
#include <iostream>

using namespace std;

unordered_map<int, int> vols;

int solution(int k, vector<int> tangerine) {
    int answer = 0, total_cnt = 0;
    for(auto t : tangerine) {
        vols[t] += 1;
    }
    priority_queue<pair<int, int>> pq;
    for (auto& v : vols) {
        pq.push({v.second, v.first});
    }

    while (!pq.empty()) {
        auto [cnt, t] = pq.top();
        pq.pop();
        total_cnt += cnt;
        answer += 1;
        
        if (total_cnt >= k) {
            break;
        }
    }
    return answer;
}