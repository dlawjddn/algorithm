/**
 * @file boj_2217.cpp
 * @brief 백준 silver4 로프
 * @version 0.1
 * @date 2024-07-25
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int weigt_cnt, answer = 0;
vector<int> weights;

int main(){
    cin>>weigt_cnt;
    weights.resize(weigt_cnt);
    for(int i=0; i<weights.size(); i++) cin>>weights[i];
    sort(weights.begin(), weights.end());
    for(int i=0; i<weights.size(); i++) answer = max(answer, (weights[i] * ((int)weights.size() - i)));
    cout<<answer;
}