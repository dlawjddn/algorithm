/**
 * @file boj_2230.cpp
 * @brief 백준 gold5 수 고르기
 * @version 0.1
 * @date 2024-07-24
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>

#define INF 1e18

using namespace std;

int node_cnt, diff, answer = INF;
vector<int> numbers;

int main() {
    cin>>node_cnt>>diff;
    numbers.resize(node_cnt);
    for(int i=0; i<node_cnt; i++) cin>>numbers[i];
    sort(numbers.begin(), numbers.end());
    int left = 0, right = 0;
    while(left <= right && right < node_cnt) {
        int cal = numbers[right] - numbers[left];
        if (cal >= diff) {
            answer = min(answer, cal);
            left++;
        } else right++;
    }
    cout<<answer;
}