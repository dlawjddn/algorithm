/**
 * @file boj_2531.cpp
 * @brief 백준 silver1 회전 초밥
 * @version 0.1
 * @date 2024-07-24
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int arr_size, food_diff, continous, coupon;
vector<int> foods;
vector<int> checked;

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>arr_size>>food_diff>>continous>>coupon;
    foods.resize(arr_size);
    checked.resize(arr_size, 0);
    for(int i=0; i<foods.size(); i++) cin>>foods[i];
    int answer = 1, cnt = 1;
    checked[coupon] = 987654321;
    for(int i=0; i<continous; i++) {
        if (checked[foods[i % arr_size]] == 0) {
            cnt++;
        }
        checked[foods[i % arr_size]]++;
    }
    answer = cnt;
    for(int i=1; i<foods.size(); i++) {
        int remove = foods[i-1];
        if (--checked[remove] == 0) cnt--;
        int add_food = foods[(i+continous-1) % arr_size];
        if (++checked[add_food] == 1) cnt++;
        answer = max(answer, cnt);
    }
    cout<<answer;
}