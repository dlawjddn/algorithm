/**
 * @file day1.cpp
 * @brief 엘리스 알고리즘 대회 DAY2 - 문자열 압축 해제
 * @version 0.1
 * @date 2024-07-08
 * 
 * @copyright Copyright (c) 2024
 * 
 * 
 * 
시간 제한: 1초
엘리스 토끼는 문자열을 직접 압축 해제하려고 합니다.

압축되지 않은 문자열 S가 주어졌을 때, 이 문자열 중 어떤 부분 문자열은 K(Q)와 같이 압축할 수 있습니다. 이것은 Q라는 문자열이 K 번 반복된다는 뜻입니다. K는 한 자릿수의 정수이고, Q는 0자리 이상의 문자열입니다.

예를 들면, 53(8)은 다음과 같이 압축을 해제할 수 있습니다.

53(8) = 5 + 3(8) = 5 + 888 = 5888

압축된 문자열이 주어졌을 때, 이 문자열을 다시 압축을 푸는 프로그램을 작성하세요.


지시사항
입력
첫째 줄에 압축된 문자열 S를 입력합니다.
S의 길이는 최대 50입니다.
문자열은 (, ), 숫자로만 구성되어 있습니다.
출력
압축되지 않은 문자열의 길이를 출력합니다.
입력 예시
11(18(72(7)))
출력 예시
26
* 
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <string>

using namespace std;

string origin;
stack<string> s;

void unzip_string() {
    for(int i=0; i<origin.size(); i++) {
        if (origin[i] != ')') {
            s.push(string(1, origin[i])); // 문자열을 스택에 넣을 때, string(1, origin[i])로 변환하여 넣는다.
        }
        else {
            string str = "";
            while(s.top() != "(") { // 스택이 비어있지 않고 "("가 아닐 때까지 pop한다.
                str += s.top(); s.pop();
            }s.pop(); // "("를 pop한다.
            
            if (!s.empty()) {
                int repeat = stoi(s.top()); s.pop();
                string result = "";
                for(int i=0; i<repeat; i++) {
                    result += str;
                }
                s.push(result);
            }
        }
    }
    int answer = 0;
    while(!s.empty()) { // 스택에 남아있는 문자열을 모두 출력한다.
        string str = s.top(); s.pop();
        answer += str.size();
    }
    cout<<answer;
}

int main() {
    cin >> origin;
    unzip_string();
    return 0;
}
