/**
 * @file 2.cpp
 * @brief PCCP 모의고사 1회 2번
 * @version 0.1
 * @date 2024-08-29
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <string>
#include <vector>

using namespace std;

int student_cnt = 0, play_cnt = 0, answer = 0;
vector<bool> visited;

void dfs(int cnt, int total_score, vector<vector<int>>& ability) {
    if (cnt == play_cnt) {
        answer = max(answer, total_score);
        return ;
    }
    for(int i=0; i<student_cnt; i++) {
        if (visited[i]) continue;
        visited[i] = true;
        dfs(cnt + 1, total_score + ability[i][cnt], ability);
        visited[i] = false;
    }
}

int solution(vector<vector<int>> ability) {
    student_cnt = ability.size();
    play_cnt = ability[0].size();
    visited.resize(student_cnt, false);
    dfs(0, 0, ability);
    return answer;
}