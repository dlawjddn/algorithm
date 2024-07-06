/**
 * @file boj_20922.cpp
 * @brief 백준 silver1 겹치는 수는 싫어
 * @version 0.1
 * @date 2024-07-06
 * 
 * @copyright Copyright (c) 2024
 * 
 * 투 포인터 공부 완료
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int arr_size, max_cnt, answer = 0;
vector<int> arr;
vector<int> counts(100001, 0);

int main(){
    cin>>arr_size>>max_cnt;
    arr.resize(arr_size + 1);
    for(int i=0; i<arr_size; i++) {
        cin>>arr[i];
    }
    int left = 0, right = 0;
    while(left <= right && right < arr_size) {
        counts[arr[right]]++;
        while(counts[arr[right]] > max_cnt) {
            counts[arr[left++]]--;
        }
        answer = max(answer, right - left + 1);
        right++;
    }
    cout<<answer;
}