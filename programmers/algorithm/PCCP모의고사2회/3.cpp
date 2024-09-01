/**
 * @file 3.cpp
 * @brief PCCP 모의고사 2회 3번
 * @version 0.1
 * @date 2024-08-31
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<int> menu, vector<int> order, int k) {
    vector<int> waiting_cnt(1000001, 0);
    int now_time = 0;
    for(int i=0; i<order.size(); i++) {
        int come_time = i * k; // 들어온 시간
        now_time = max(now_time, come_time);
        int out_time = now_time + menu[order[i]]; // 현재시간 + 제조시간
        waiting_cnt[come_time] += 1;
        waiting_cnt[out_time] -= 1;
        now_time += menu[order[i]];
    }
    for(int i=1; i<waiting_cnt.size(); i++) {
        waiting_cnt[i] += waiting_cnt[i-1];
    }
    return *max_element(waiting_cnt.begin(), waiting_cnt.end());
}