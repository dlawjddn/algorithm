/**
 * @file boj_4949.cpp
 * @brief 백준 silver4 균형잡힌 세상
 * @version 0.1
 * @date 2024-07-08
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <vector>
#include <stack>
#include <string>

using namespace std;

int main(){
    while(1) {
        string str; getline(cin, str);
        //cout<<str<<"\n";
        if (str == ".") break;
        stack<char> s;
        bool answer = true;
        for(int i=0; i<str.size(); i++) {
            if (str[i] == '[' || str[i] == '(') s.push(str[i]);
            else if (str[i] == ')' || str[i] == ']') {
                if (s.empty()) {
                    answer = false;
                    break;
                }
                if (str[i] == ')' && s.top() == '(') {
                    s.pop();
                }
                else if (str[i] == ']' && s.top() == '[') {
                    s.pop();
                }
                else {
                    answer = false;
                    break;
                }
            }
            else continue;
        }
        if (!answer || s.size() != 0) cout<<"no\n";
        else cout<<"yes\n";
    }
}