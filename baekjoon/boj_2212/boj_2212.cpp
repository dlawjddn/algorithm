/**
 * @file boj_2212.cpp
 * @brief 백준 gold5 센서
 * @version 0.1
 * @date 2024-07-26
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int arr_size, group_cnt;
vector<int> numbers;
priority_queue<int, vector<int>, greater<int> > pq;

int main(){
    cin>>arr_size>>group_cnt;
    numbers.resize(arr_size);
    for(int i=0; i<arr_size; i++) cin>>numbers[i];
    sort(numbers.begin(), numbers.end());
    for(int i=1; i<arr_size; i++) pq.push(numbers[i] - numbers[i-1]);

    int answer = 0, pick_up = arr_size - group_cnt;
    while(pick_up > 0) {
        answer += pq.top(); pq.pop();
        pick_up--;
    }
    cout<<answer;
}