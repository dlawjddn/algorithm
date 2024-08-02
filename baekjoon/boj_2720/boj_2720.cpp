/**
 * @file boj_2720.cpp
 * @brief 백준 bronze3 세탁소 사장 동혁
 * @version 0.1
 * @date 2024-08-02
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>

using namespace std;

int main(){
    int test_case; cin>>test_case;
    for(int t=0; t<test_case; t++) {
        int money; cin>>money;
        cout<< money/25 <<" ";
        money %= 25;
        cout<< money/10 <<" ";
        money %= 10;
        cout<< money/5 <<" ";
        money %= 5;
        cout<< money/1 <<"\n";
    }
}