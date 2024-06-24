/**
 * @file 올바른괄호의개수_12929.cpp
 * @brief 프로그래머스 lv.4 올바른 괄호의 개수
 * @version 0.1
 * @date 2024-06-24
 * 
 * @copyright Copyright (c) 2024
 * 
 * dp만 생각하다가 dfs를 생각하지 못했다.. 흠.. 
 * dp 문제 같아도 방정식이 생각나지 않으면 dfs로 완전탐색을 통해 해결할 수 있는지 먼저 파악해야겠다!
 * 
 */
#include <string>
#include <vector>

using namespace std;

int answer = 0;

void dfs(int n, int open, int close) {
    if (open > n || close > n) return ;
    if (open < close) return ; 
    
    if (open == n && close == n) {
        answer += 1;
        return ;
    }
    
    dfs(n, open + 1, close);
    dfs(n, open, close + 1);
}

int solution(int n) {
    dfs(n, 0, 0);
    return answer;
}