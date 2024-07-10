/**
 * @file boj_15926.cpp
 * @brief 백준 gold3 현욱은 괄호왕이야!! 
 * @version 0.1
 * @date 2024-07-11
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>

using namespace std;

int str_size;
string str;
stack<int> s;
vector<bool> check;

void print_check() {
    for(int i=0; i<check.size(); i++) cout<<check[i]<<" ";
    cout<<"\n";
}

int find_longest() {
    int answer = 0, temp_answer = 0;
    for(int i=0; i<check.size(); i++) {
        if (check[i]) {
            temp_answer++;
            answer = max(answer, temp_answer);
        } else {
            temp_answer = 0;
        }
    }
    return answer;
}

int main(){
    cin>>str_size;
    cin>>str;
    check.resize(str_size, false);
    for(int i=0; i<str.size(); i++) {
        if (str[i] == '(') s.push(i);
        else if (!s.empty() && str[i] == ')') {
            if (str[s.top()] == '(') {
                check[s.top()] = true;
                check[i] = true;
                s.pop();
            }
        }
    }
    //print_check();
    cout<<find_longest();
}