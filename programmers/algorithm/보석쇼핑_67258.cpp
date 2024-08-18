/**
 * @file 보석쇼핑_67258.cpp
 * @brief 프로그래머스 lv.3 보석 쇼핑
 * @version 0.1
 * @date 2024-08-18
 * 
 * @copyright Copyright (c) 2024
 * 
 * 다시 풀자
 * 
 */
#include <string>
#include <vector>
#include <unordered_map>
#include <set>

using namespace std;

vector<int> solution(vector<string> gems) {
    vector<int> answer;
    set<string> unique_gems(gems.begin(), gems.end());
    
    int unique_cnt = unique_gems.size();
    int left = 0, right = 0, min_length = gems.size();
    int answer_left = 1, answer_right = gems.size();

    unordered_map<string, int> select_cnt;
    
    while(right < gems.size()) {
        select_cnt[gems[right]]++;
        while(select_cnt.size() == unique_cnt) {
            int len = right - left + 1;
            if (len < min_length) {
                answer_left = left + 1;
                answer_right = right + 1;
                min_length = len;
            }
            select_cnt[gems[left]]--;
            if (select_cnt[gems[left]] == 0) {
                select_cnt.erase(gems[left]);
            }
            left++;
        }
        right++;
    }
    return {answer_left, answer_right};
}