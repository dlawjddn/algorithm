/**
 * @file boj_17609.cpp
 * @brief 백준 gold5 회문
 * @version 0.1
 * @date 2024-07-12
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int test_case;

int is_pellindrome(string str, int left, int right, int del){
    while(left < right) {
        if (str[left] != str[right]) {
            if (del == 0) {
                if (is_pellindrome(str, left+1, right, del + 1) == 0 || is_pellindrome(str, left, right-1, del + 1) == 0) return 1;
                return 2;
            }else return 2;
        }
        left++;
        right--;
    }
    return 0;
}

int main(){
    cin>>test_case;
    for(int i=0; i<test_case; i++) {
        string str; cin>>str;
        cout<<is_pellindrome(str, 0, str.size() - 1, 0)<<"\n";
    }
}