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
#include <set>

using namespace std;

set<int> s;

int main(){
    int num_cnt; cin>>num_cnt;
    for(int i=0; i<num_cnt; i++) {
        int num; cin>>num;
        s.insert(num);
    }
    int check_cnt; cin>>check_cnt;
    for(int i=0; i<check_cnt; i++) {
        int num; cin>>num;
        if (s.find(num) != s.end()) cout<<"1\n";
        else cout<<"0\n";
    }
}