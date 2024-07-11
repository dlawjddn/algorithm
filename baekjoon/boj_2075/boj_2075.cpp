/**
 * @file boj_2075.cpp
 * @brief 백준 silver2 N번째 큰 수
 * @version 0.1
 * @date 2024-07-11
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int sq_size;
vector<int> arr;

int main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin>>sq_size;
    arr.resize(sq_size * sq_size);
    for(int i=0; i<sq_size * sq_size; i++) cin>>arr[i];
    sort(arr.begin(), arr.end());
    cout<<arr[sq_size * sq_size - sq_size];
}