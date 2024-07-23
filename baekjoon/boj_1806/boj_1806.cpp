/**
 * @file boj_1806.cpp
 * @brief 백준 gold4 부분합
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

int arr_size, goal_number;
vector<int> numbers;
vector<int> sums;

int main(){
    cin>>arr_size>>goal_number;
    numbers.resize(arr_size, 0);
    sums.resize(arr_size, 0);
    for(int i=0; i<arr_size; i++) {
        cin>>numbers[i];
        if (i != 0) sums[i] = sums[i-1] + numbers[i-1];
    }
    int left = 0, right = 0, answer = 100001;
    while(left <= right && right < arr_size && left < arr_size) {
        //cout<<left<<" "<<right<<"\n";
        int sum = sums[right] - sums[left] + numbers[right];
        if (sum >= goal_number) {
            answer = min(answer, right - left + 1);
            left++;
        }else right++;
    }
    cout<<((answer == 100001) ? 0 : answer);
}