/**
 * @file 징검다리건너기_64062.cpp
 * @brief 프로그래머스 lv.3 2019 카카오 인턴십 징검다리 건너기
 * @version 0.1
 * @date 2024-08-18
 * 
 * @copyright Copyright (c) 2024
 * 
 * 너무 대중적인 이분탐색 문제
 * 
 */
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<int> stones, int k) {
    int answer = 0;
    int left = 0, right = *max_element(stones.begin(), stones.end());
    while(left <= right) {
        int mid = (left + right) / 2;
        int cnt = 0;
        bool success = true;
        for(int i=0; i<stones.size(); i++) {
            int num = stones[i] - mid;
            if (num < 0) cnt++;
            else cnt = 0;
            
            if (cnt >= k) {
                success = false;
                break;
            }
        }
        if (success) {
            answer = max(answer, mid);
            left = mid + 1;
        } else right = mid - 1;
    }
    return answer;
}