#include <string>
#include <vector>
#include <queue>

using namespace std;

queue<pair<string, int> > q;
int visited[50][50];

// 단어변환
bool canChange(string s1, string s2){
    bool flag = false;
    for(int i=0; i<s1.size(); i++){
        if (s1[i] != s2[i]){
            if (flag) return false;
            flag = true;
        }
    }
    return true;
}
int getIndex(vector<string> words, string s){
    for(int i=0; i<words.size(); i++){
        if (words[i] == s) return i;
    }
}
int bfs(vector<string> words, string begin, string target){
    q.push(make_pair(begin, 0));
    while(!q.empty()){
        string now = q.front().first;
        int cnt = q.front().second; q.pop();
        if (now == target) return cnt;
        for(int d=0; d<words.size(); d++){
            if (now == words[d]) continue;
            string next = words[d];
            int n_cnt = cnt + 1;
            if (canChange(now, next) && visited[getIndex(words, next)][n_cnt] == 0){
                q.push(make_pair(next, n_cnt));
                visited[getIndex(words, next)][n_cnt] = 1;
            }
        }
    }
    return 0;
}
int solution(string begin, string target, vector<string> words) {
    int answer = 0;
    return bfs(words, begin, target);
}

/**
 * @file 단어변환_43163.cpp
 * @brief 프로그래머스 lv.3 단어변환
 * @version 0.1
 * @date 2024-08-17
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <string>
#include <vector>
#include <iostream>

#define INF 987654321

using namespace std;

int answer = INF;
vector<bool> visited;

bool compare_string(string now, string next) {
    int diff = 0;
    for(int i=0; i<now.size(); i++) {
        if(now[i] != next[i]) diff++;
        if (diff >= 2) return false;
    }
    return true;
}

void dfs(int cnt, string now, string target, vector<string>& words) {
    if (now == target) {
        answer = min(answer, cnt);
        return ;
    }
    for(int i=0; i<words.size(); i++) {
        if (visited[i] || !compare_string(now, words[i])) continue;
        visited[i] = true;
        dfs(cnt + 1, words[i], target, words);
        visited[i] = false;
    }
}

int solution(string begin, string target, vector<string> words) {
    visited.resize(words.size(), false);
    dfs(0, begin, target, words);
    if (answer == INF) return 0;
    return answer;
}