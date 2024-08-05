/**
 * @file 택배상자_131704.cpp
 * @brief 프로그래머스 lv.2 택배 상자
 * @version 0.1
 * @date 2024-08-06
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <string>
#include <vector>
#include <stack>

using namespace std;

int solution(vector<int> order) {
    int answer = 0;
    stack<int> s;
    for(int i=1; i<=order.size(); i++) {
        if (order[answer] == i) answer++;
        else s.push(i);
        while(!s.empty() && s.top() == order[answer]) {
            s.pop();
            answer++;
        }
    }
    return answer;
}