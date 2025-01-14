#include <iostream>
#include <string>
#include <stack>

using namespace std;

int solution(string s){
    stack<char> stack;
    for(int i=0; i<s.size(); i++) {
        if (stack.empty() || s[i] != stack.top()) {
            stack.push(s[i]);
            continue;
        }
        if (s[i] == stack.top()) stack.pop();
    }
    if (stack.size() == 0) return 1;
    return 0;
}