/**
 * @file boj_1789.cpp
 * @brief 백준 silver5 수들의 합
 * @version 0.1
 * @date 2024-08-04
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>

using namespace std;

long long goal;

int main(){
    cin>>goal;
    long long sum = 0;
    long long num = 1;
    while(sum <= goal) {
        sum += num;
        //cout<<sum<<"\n";
        num++;
    }
    cout<<num - 2;
}