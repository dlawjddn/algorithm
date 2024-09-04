/**
 * @file 짝지어제거하기_12973.cpp
 * @brief 프로그래머스 짝지어 제거하기 lv.2
 * @version 0.1
 * @date 2024-05-29
 * 
 * @copyright Copyright (c) 2024
 * 
 * 이 문제를 보고 5분만에 스택임을 떠올렸다..! 성장했다!!
 */
#include <iostream>
#include <string>
#include <stack>

using namespace std;

int solution(string alphas){
    stack<char> s;
    for(int i=0; i<alphas.size(); i++){
        if (s.empty()){
            s.push(alphas[i]);
            continue;
        }
        else {
            if (s.top() == alphas[i]){
                s.pop();
                continue;
            }
            else {
                s.push(alphas[i]);
            }
        }
    }
    if (s.empty())
        return 1;
    else
        return 0;
}
/**
 * @file 짝지어제거하기_12973.cpp
 * @brief 프로그래머스 lv.2 짝 지어 제거하기
 * @version 0.1
 * @date 2024-09-05
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <string>
#include <stack>

using namespace std;

stack<char> s;

int solution(string str){
    for(char a : str) {
        if (s.empty() || !s.empty() && s.top() != a) {
            s.push(a);
            continue;
        }
        s.pop();
    }
    if (s.empty()) return 1;
    return 0;
}