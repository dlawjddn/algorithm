/**
 * @file 슈퍼컴퓨터클러스터.cpp
 * @brief [HSAT 4회 정기 코딩 인증평가 기출] 슈퍼컴퓨터 클러스터
 * @version 0.1
 * @date 2024-09-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int computer_cnt; 
unsigned long long answer = 0, max_budget=0;
vector<long long> computer;

int main(int argc, char** argv) {
    cin >> computer_cnt >> max_budget;
    computer.resize(computer_cnt, 0);
    for (int i = 0; i < computer_cnt; i++) {
        cin >> computer[i];
    }
    sort(computer.begin(), computer.end());
    
    unsigned long long left = computer.front(); // 가능한 성능의 최솟값
    unsigned long long right = computer.back() + sqrt(max_budget); // 가능한 성능의 최댓값
    
    while (left <= right) {
        unsigned long long mid = (left + right) / 2;
        unsigned long long cost = 0;
        bool over = false;
        
        for (int i = 0; i < computer.size(); i++) {
            if (computer[i] < mid) {
                unsigned long long diff = mid - computer[i];
                cost += diff * diff;
                if (cost > max_budget) {
                    over = true;
                    break;
                }
            } else break;
        }
        
        if (over) {
            right = mid - 1;
        } else {
            answer = mid;
            left = mid + 1;
        }
    }
    
    cout << answer;
}
