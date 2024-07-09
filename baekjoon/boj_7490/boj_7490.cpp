/**
 * @file boj_7490.cpp
 * @brief 백준 gold5 0 만들기
 * @version 0.1
 * @date 2024-07-09
 * 
 * @copyright Copyright (c) 2024
 * 
 * 원트 컷~!
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

string sign[3]={"+", "-", " "};
vector<string> answer;

void check_zero(string str) {
    int num = 0, result = 0, last_sign = 0;
    for(int i=0; i<str.size(); i++) {
        if (str[i] == '+' || str[i] == '-') {
            if (last_sign == 0) result += num;
            else if (last_sign == 1) result -= num;

            if (str[i] == '+') last_sign = 0;
            else last_sign = 1;

            num = 0;
        }
        else if (str[i] == ' ') continue;
        else {
            num = num * 10 + (str[i] - '0');
        }
    }
    if (last_sign == 0) result += num;
    else result -= num;

    if (result == 0) answer.push_back(str);
}

void dfs(int limit, int num, string str) {
    str += to_string(num);
    if (limit == num) {
        check_zero(str);
        return ;
    }
    for(int d=0; d<3; d++) {
        dfs(limit, num + 1, str + sign[d]);
    }
}

int main(){
    int test_case; cin>>test_case;
    for(int i=0; i<test_case; i++) {
        int limit; cin>>limit;
        dfs(limit, 1, "");
        sort(answer.begin(), answer.end());
        for(string a : answer) cout<<a<<"\n";
        answer.clear(); cout<<"\n";
    }
}