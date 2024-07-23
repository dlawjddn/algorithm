/**
 * @file boj_1484.cpp
 * @brief 백준 gold5 다이어트
 * @version 0.1
 * @date 2024-07-23
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

long long plus_weight;
vector<int> answer;

int main(){
    cin>>plus_weight;
    int left = 1, right = 1;
    while(1) {
        long long result = (right * right) - (left * left);
        if (result == plus_weight) {
            answer.push_back(right);
            right++;
            continue;
        }
        if (right - left == 1 && result > plus_weight) break;
        if (result > plus_weight) left++;
        else right++;
    }
    if(answer.empty()) cout<<"-1";
    else {
        sort(answer.begin(), answer.end());
        for(auto a : answer) cout<<a<<"\n";
    }
}