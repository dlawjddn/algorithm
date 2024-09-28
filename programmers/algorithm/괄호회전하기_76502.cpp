#include <string>
#include <vector>
#include <stack>
#include <iostream>

using namespace std;

int solve(string brakets){
    int answer = 0;
    stack<char> s;
    for(int i=0; i<brakets.size(); i++){
        bool wrong = false;
        for(int j=i; j < i + brakets.size(); j++){
            int idx = j % brakets.size();
            // 여는 괄호라면 stack.push
            if (brakets[idx] == '[' || brakets[idx] == '{' || brakets[idx] == '('){
                s.push(brakets[idx]);
            } 
            // 닫는 괄호라면 일치하는지 파악
            else {
                char check = s.top();
                if (check == '{' && brakets[idx] == '}'){
                    s.pop();
                } else if (check == '(' && brakets[idx] == ')'){
                    s.pop();
                } else if (check == '[' && brakets[idx] == ']'){
                    s.pop();
                } else {
                    wrong = true;
                    break;
                }
            }
        }
        if (!wrong && s.size() == 0)
            answer++;
    }
    return answer;
}

int solution(string s) {
    return solve(s);
}
/**
 * @file 괄호회전하기_76502.cpp
 * @brief 프로그래머스 lv.2 괄호 회전하기
 * @version 0.1
 * @date 2024-09-28
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <string>
#include <vector>
#include <stack>
#include <iostream>

using namespace std;

bool check_correct(string str) {
    stack<char> s;
    for(auto c : str) {
        if (s.empty()) {
            s.push(c);
            continue;
        }
        if (s.top() == '{' && c == '}') s.pop();
        else if (s.top() == '[' && c == ']') s.pop();
        else if (s.top() == '(' && c == ')') s.pop();
        else s.push(c);
    }
    if (s.empty()) return true;
    return false;
}

int solution(string s) {
    int answer = 0;
    s += s;
    int limit = s.size() / 2;
    for(int start = 0; start<limit; start++) {
        if (check_correct(s.substr(start, limit))) answer++;
    }
    return answer;
}