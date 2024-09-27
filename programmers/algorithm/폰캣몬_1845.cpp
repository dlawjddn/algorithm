/**
 * @file 폰캣몬_1845.cpp
 * @brief 프로그래머스 lv.1 폰캣몬
 * @version 0.1
 * @date 2024-09-27
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int solution(vector<int> nums){
    set<int> unique_nums(nums.begin(), nums.end());
    return min(unique_nums.size(), nums.size() / 2);
}