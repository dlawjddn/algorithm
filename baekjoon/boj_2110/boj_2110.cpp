/**
 * @file boj_2110.cpp
 * @brief 백준 gold4 공유기 설치
 * @version 0.1
 * @date 2024-07-23
 * 
 * @copyright Copyright (c) 2024
 * 
 * 이분탐색.. left, right에 대한 범위 설정을 좀 더 디테일하게 생각하기..
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int home_cnt, router_cnt, answer;
vector<int> homes;

int main(){
    cin>>home_cnt>>router_cnt;
    homes.resize(home_cnt);
    for(int i=0; i<home_cnt; i++) cin>>homes[i];
    sort(homes.begin(), homes.end());
    int left = 1, right = homes.back() - homes[0] + 1;
    while(left <= right) {
        int mid = (left + right) / 2;
        int last = homes[0];
        int cnt = 1;
        for(auto home : homes) {
            if (home - last >= mid) {
                cnt++;
                last = home;
            }
        }
        if (cnt >= router_cnt) {
            answer = max(answer, mid);
            left = mid + 1;
        }
        else right = mid - 1;
    }
    cout<<answer;
}