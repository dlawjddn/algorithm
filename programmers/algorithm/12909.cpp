#include<string>
#include <iostream>
#include <stack>

using namespace std;

// 올바른 괄호
bool solution(string s)
{
    bool ans = true;
    stack<char> stack;
    for(int i=0; i<s.size(); i++){
        if (stack.empty()) stack.push(s[i]);
        else {
            if (stack.top() == '(' && s[i] == ')')
                stack.pop();
            else stack.push(s[i]);
        }
    }
    if (stack.empty()) return true;
    return false;

    return ans;
}