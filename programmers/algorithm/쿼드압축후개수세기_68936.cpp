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
/**
 * @file 쿼드압축후개수세기_68936.cpp
 * @brief 프로그래머스 lv.2 퀴드 압축 후 개수 세기
 * @version 0.1
 * @date 2024-09-05
 * 
 * @copyright Copyright (c) 2024
 * 
 * 와 근데 개소름이다.. 안 보고 짰는데 똑같이 썼네
 * 
 */
#include <string>
#include <vector>

using namespace std;

int zero = 0, one = 0;

void dfs(int sy, int sx, int size, vector<vector<int>>& arr) {
    if (size == 1) {
        // 끝까지 압축 안되는 경우 -> 최종 개수 파악
        (arr[sy][sx] == 1) ? one++ : zero++;
        return;
    }
    int zero_cnt = 0, one_cnt = 0;
    // 제시된 범위 탐색
    for(int y=sy; y<sy+size; y++) {
        for(int x=sx; x<sx+size; x++) {
            (arr[y][x] == 1) ? one_cnt++ : zero_cnt++;
        }
    }
    // 압축이 가능하다면
    if (zero_cnt == 0 || one_cnt == 0) {
        (zero_cnt == 0) ? one++ : zero++;
        return ;
    }
    // 압축이 안된 경우 -> 4개로 나누기
    int next_size = size / 2;
    dfs(sy, sx, next_size, arr);
    dfs(sy + next_size, sx, next_size, arr);
    dfs(sy, sx + next_size, next_size, arr);
    dfs(sy + next_size, sx + next_size, next_size, arr);
}

vector<int> solution(vector<vector<int>> arr) {
    dfs(0, 0, arr.size(), arr);
    return {zero, one};
}