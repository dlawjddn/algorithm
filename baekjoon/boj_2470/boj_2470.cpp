/**
 * @file boj_2470.cpp
 * @brief 백준 gold5 두 용액
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

int main(){
    int arr_size; cin>>arr_size;
    vector<int> numbers(arr_size);
    for(int i=0; i<arr_size; i++) cin>>numbers[i];
    sort(numbers.begin(), numbers.end());
    int left = 0, right = arr_size - 1, answer = 2000000001;
    int min_left = 0, min_right = 0;
    while(left != right) {
        int sum = numbers[left] + numbers[right];
        if (answer > abs(sum)) {
            answer = abs(sum);
            min_left = numbers[left];
            min_right = numbers[right];
        }
        if (sum < 0) left++;
        else if (sum > 0) right--;
        else break;
    }
    cout<<min_left<<" "<<min_right;
}