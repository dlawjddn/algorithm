/**
 * @file set_boj_1920.cpp
 * @brief 백준 silver4 수 찾기
 * @version 0.1
 * @date 2024-07-10
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> numbers;

void binary_search(int limit, int dest) {
    int left = 0, right = limit - 1;
    while(left <= right) {
        int mid = (left + right) / 2;
        if (numbers[mid] == dest) {
            cout<<"1\n";
            return ;
        }
        else if (numbers[mid] > dest) {
            right = mid - 1;   
        } else {
            left = mid + 1;
        }
    }
    cout<<"0\n";
    return ;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int num_cnt; cin>>num_cnt;
    numbers.resize(num_cnt);
    for(int i=0; i<num_cnt; i++) cin>>numbers[i];
    sort(numbers.begin(), numbers.end());

    int check_cnt; cin>>check_cnt;
    for(int i=0; i<check_cnt; i++) {
        int num; cin>>num;
        binary_search(num_cnt, num);
    }
}