/**
 * @file 더맵게_42626.cpp
 * @brief 프로그래머스 lv.2 더 맵게
 * @version 0.1
 * @date 2024-09-10
 * 
 * @copyright Copyright (c) 2024
 * 
 * pq의 사이즈가 2개 이상 있을 때 다음 스텝으로 넘어가기 가능
 * 
 */
#include <string>
#include <vector>
#include <queue>

using namespace std;

int solution(vector<int> scoville, int K) {
    int answer = 0;
    priority_queue<int, vector<int>, greater<int> > pq(scoville.begin(), scoville.end());
    while(!pq.empty()) {
        if (pq.top() >= K) {
            return answer;
        }
        if (pq.size() < 2) return -1;
        answer++;
        int spicy1 = pq.top(); pq.pop();
        int spicy2 = pq.top(); pq.pop();
        pq.push(spicy1 + 2 * spicy2);
    }
    return -1;
}