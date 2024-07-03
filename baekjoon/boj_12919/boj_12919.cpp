/**
 * @file boj_12919.cpp
 * @brief 백준 gold5 A와 B 2
 * @version 0.1
 * @date 2024-07-03
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

bool can_find = false;

void bfs(string s, string t) {
    queue<string> q;
    q.push(t);
    while(!q.empty()) {
        string now = q.front(); q.pop();
        if (now == s) {
            can_find = true;
            break;            
        }

        if (now[now.size() - 1] == 'A') {
            string next = now.substr(0, now.size()-1);
            if (next.size() >= s.size()) q.push(next);
        }

        if (now[0] == 'B') {
            string next = now.substr(1, now.size()-1);
            reverse(next.begin(), next.end());
            if (next.size() >= s.size()) q.push(next);
        }
    }
    if (can_find) cout<<1;
    else cout<<0;
}

int main(){
    string s, t; cin>>s>>t;
    bfs(s, t);
}