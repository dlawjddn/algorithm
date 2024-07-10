/**
 * @file boj_2504.cpp
 * @brief 백준 gold5 괄호의 값
 * @version 0.1
 * @date 2024-07-11
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

string origin;

bool is_perfect() {
    stack<char> s;
    for(int i=0; i<origin.size(); i++) {
        if (origin[i] == '(' || origin[i] == '[') s.push(origin[i]);
        else {
            if (s.empty()) return false;
            if (origin[i] == ')' && s.top() == '(') {
                s.pop();
                continue;
            }
            if (origin[i] == ']' && s.top() == '[') {
                s.pop();
                continue;
            }
            return false;
        }
    }
    if (s.size() == 0) return true;
    return false;
}

int cal_result() {
    int mul = 1, result = 0;
    for(int i=0; i<origin.size(); i++) {
        if (origin[i] == '(') mul *= 2;
        else if (origin[i] == '[') mul *= 3;
        else if (origin[i] == ')') {
            if (origin[i-1] == '(') {
                result += mul;
            }
            mul /= 2;
        }
        else {
            if (origin[i-1] == '[') {
                result += mul;
            }
            mul /= 3;
        }
    }
    return result;
}

int main(){
    cin>>origin;
    if (!is_perfect()) cout<<"0";
    else cout<<cal_result();
}