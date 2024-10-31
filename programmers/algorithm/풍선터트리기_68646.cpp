/**
 * @file 풍선터트리기_68646.cpp
 * @brief 프로그래머스 lv.3 풍선터트리기
 * @version 0.1
 * @date 2024-10-31
 * 
 * @copyright Copyright (c) 2024
 * 
 * 그리디~ 하게 생각하기
 * 
 */
#include <string>
#include <vector>
#include <algorithm>

#define MAX 1000000001

using namespace std;

int solution(vector<int> a) {
    int answer = 0;
    vector<int> left_min = vector<int>(a.size(), MAX);
    vector<int> right_min = vector<int>(a.size(), MAX);
    
    int min_value = MAX;
    
    for(int i=0; i<a.size(); i++) {
        min_value = min(min_value, a[i]);
        left_min[i] = min_value;
    }
    
    min_value = MAX;
    
    for(int i=a.size() - 1; i>=0; i--) {
        min_value = min(min_value, a[i]);
        right_min[i] = min_value;
    }
    
    for(int i=1; i<a.size() - 1; i++) {
        if (left_min[i-1] < a[i] && right_min[i+1] < a[i]) continue;
        answer++;
    }
    
    return answer + 2;
}