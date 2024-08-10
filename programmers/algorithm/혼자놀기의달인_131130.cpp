/**
 * @file 혼자놀기의달인_131130.cpp
 * @brief 프로그래머스 lv.2 혼자 놀기의 달인
 * @version 0.1
 * @date 2024-08-10
 * 
 * @copyright Copyright (c) 2024
 * 
 * 캬!
 * 
 */
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int answer = 0;
vector<int> visited;

void dfs_group2(vector<int>& cards, int idx, int cnt2, int cnt1) {
    if (visited[idx] == 1 || visited[idx] == 2) {
        // 1번 그룹의 상자를 열어야 하거나, 열었던 상자를 만난 경우
        answer = max(answer, cnt1 * cnt2);
        return ;
    }
    visited[idx] = 2;
    dfs_group2(cards, cards[idx]-1, cnt2+1, cnt1);
    visited[idx] = 0;
}

void dfs_group1(vector<int>& cards, int idx, int cnt) {
    if (visited[idx] == 1) {
        // 열었던 상자를 만난 경우
        for(int i=0; i<cards.size(); i++) {
            if (visited[i] == 1) continue;
            dfs_group2(cards, i, 0, cnt);
        }
        return ;
    }
    visited[idx] = 1;
    dfs_group1(cards, cards[idx]-1, cnt+1);
    visited[idx] = 0;
}

void solve(vector<int>& cards) {
    for(int i=0; i<cards.size(); i++) {
        dfs_group1(cards, i, 0);
    }
}

int solution(vector<int> cards) {
    visited.resize(cards.size(), 0);
    solve(cards);
    return answer;
}