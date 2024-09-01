/**
 * @file 2.cpp
 * @brief PCCP 모의고사 2회 2번
 * @version 0.1
 * @date 2024-08-31
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int solution(vector<int> ability, int number) {
    int answer = 0;
    priority_queue<int, vector<int>, greater<int> > pq(ability.begin(), ability.end());
    for(int i=0; i<number; i++) {
        int score1 = pq.top(); pq.pop();
        int score2 = pq.top(); pq.pop();
        pq.push(score1 + score2);
        pq.push(score1 + score2);
    }
    while(!pq.empty()) {
        answer += pq.top(); pq.pop();
    }
    return answer;
}