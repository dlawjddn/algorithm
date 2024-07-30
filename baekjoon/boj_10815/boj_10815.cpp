/**
 * @file boj_10815.cpp
 * @brief 백준 silver5 숫자 카드
 * @version 0.1
 * @date 2024-07-30
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <set>

using namespace std;

int number_cnt, find_cnt;
set<int> numbers;

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>number_cnt;
    for(int i=0; i<number_cnt; i++) {
        int num; cin>>num;
        numbers.insert(num);
    }
    cin>>find_cnt;
    for(int i=0; i<find_cnt; i++) {
        int num; cin>>num;
        if (numbers.find(num) != numbers.end()) cout<<"1 ";
        else cout<<"0 ";
    }
}