/**
 * @file boj_1654.cpp
 * @brief 백준 silver2 랜선 자르기
 * @version 0.1
 * @date 2024-07-30
 * 
 * @copyright Copyright (c) 2024
 * 
 * 자료형 조심.. 또 조심..!
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int arr_size;
long long need, answer;
vector<int> arr;

int main(){
    cin>>arr_size>>need;
    arr.resize(arr_size);
    for(int i=0; i<arr_size; i++) cin>>arr[i];
    sort(arr.begin(), arr.end());

    long long left = 1, right = arr.back();
    while(left <= right) {
        long long mid = (left + right) / 2;
        long long result = 0;
        for(int i=0; i<arr.size(); i++) {
            result += (arr[i] / mid);
        }
        if (result >= need) {
            left = mid + 1;
            answer = mid;
        } else right = mid - 1;
    }
    cout<<answer;
}