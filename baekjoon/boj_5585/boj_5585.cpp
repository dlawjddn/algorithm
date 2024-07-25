/**
 * @file boj_5585.cpp
 * @brief 백준 bronze2 거스름돈
 * @version 0.1
 * @date 2024-07-25
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>

using namespace std;

int main(){
    int price; cin>>price;
    int change = 1000 - price;
    int answer = 0;
    answer += (change / 500);
    change %= 500;
    answer += (change / 100);
    change %= 100;
    answer += (change / 50);
    change %= 50;
    answer += (change / 10);
    change %= 10;
    answer += (change / 5);
    change %= 5;
    answer += (change / 1);
    cout<<answer;
}