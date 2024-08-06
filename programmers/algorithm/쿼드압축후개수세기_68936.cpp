/**
 * @file 쿼드압축후개수세기_68936.cpp
 * @author your name (you@domain.com)
 * @brief 프로그래머스 lv.2 쿼드압축 후 개수 세기
 * @version 0.1
 * @date 2024-08-06
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <string>
#include <vector>
#include <iostream>

using namespace std;

int one_cnt = 0, zero_cnt = 0;

void dfs(vector<vector<int>>& arr, int sy, int sx, int len) {
    if (len == 1) {
        (arr[sy][sx] == 0) ? zero_cnt++ : one_cnt++;
        return;
    }
    // 1. 현재 영역에 대해 동일한 숫자인지 확인하기
    int cnt_one = 0, cnt_zero = 0;
    for(int y=sy; y<sy+len; y++) {
        for(int x=sx; x<sx+len; x++) {
            (arr[y][x] == 0) ? cnt_zero++ : cnt_one++;
        }
    }
    // 2. 현재 영역이 압축이 가능한 경우 stop
    if (cnt_zero == 0 || cnt_one == 0) {
        (cnt_zero == 0) ? one_cnt++ : zero_cnt++;
        return ;
    }
    
    // 3. 현재 영역이 압축이 불가능해서 더 작은 영역에 대해서 확인을 가능
    int nlen = len / 2;
    dfs(arr, sy, sx, nlen);
    dfs(arr, sy + nlen, sx, nlen);
    dfs(arr, sy, sx + nlen, nlen);
    dfs(arr, sy + nlen, sx + nlen, nlen);
    
}

vector<int> solution(vector<vector<int>> arr) {
    vector<int> answer;
    dfs(arr, 0, 0, arr.size());
    answer.push_back(zero_cnt);
    answer.push_back(one_cnt);
    return answer;
}