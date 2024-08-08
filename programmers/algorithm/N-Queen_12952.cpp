/**
 * @file N-Queen_12952.cpp
 * @brief 프로그래머스 lv.2 N-Queen
 * @version 0.1
 * @date 2024-08-08
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int answer = 0;
vector<int> maps;

void print_maps() {
    for(int i=1; i<maps.size(); i++) cout<<maps[i]<<" ";
    cout<<"\n";
}

bool check_pos(int sy, int sx) {
    for(int y=1; y<sy; y++) {
        if (maps[y] == sx) return false;
        if (abs(sy - y) == abs(sx - maps[y])) return false;
    }
    return true;
}

void dfs(int n, int cnt) {
    //print_maps();
    if (n < cnt) {
        answer++;
        return ;
    }
    for(int x=1; x<=n; x++) {
        if (!check_pos(cnt, x)) continue;
        maps[cnt] = x;
        dfs(n, cnt+1);
        maps[cnt] = 0;
    }
}

int solution(int n) {
    maps.resize(n+1, 0);
    dfs(n, 1);
    return answer;
}