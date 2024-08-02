/**
 * @file boj_1477.cpp
 * @brief 백준 gold4 휴게소 세우기
 * @version 0.1
 * @date 2024-08-02
 * 
 * @copyright Copyright (c) 2024
 * 
 * 흠.. 더 공부하자 이분탐색..
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int exist_cnt, more_cnt, total_length, answer;
vector<int> stores;

int main(){
    cin>>exist_cnt>>more_cnt>>total_length;
    stores.push_back(0);
    stores.push_back(total_length);
    for(int i=0; i<exist_cnt; i++) {
        int num; cin>>num;
        stores.push_back(num);
    }
    sort(stores.begin(), stores.end());
    int left = 1, right = total_length;
    while(left <= right) {
        int mid = (left + right) / 2;
        int cnt = 0;
        for(int i=1; i<stores.size(); i++) {
            int diff = stores[i] - stores[i-1];
            cnt += (diff / mid);
            if(diff % mid == 0) cnt--;
        }
        if (cnt > more_cnt) left = mid + 1;
        else {
            right = mid - 1;
            answer = mid;
        }
    }
    cout<<answer;
}