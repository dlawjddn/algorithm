#include <string>
#include <vector>
#include <iostream>
#include <stack>

using namespace std;

string remake(string s, int n) {
    string result = "";
    for(int i=0; i<s.size(); i++) {
        result += s[(i+n) % s.size()];
    }
    return result;
}

int solution(string s) {
    int answer = 0;
    for(int i=0; i<s.size(); i++) {
        string str = remake(s, i);
        stack<char> stack;
        
        for(int j=0; j<str.size(); j++) {
            if (stack.empty() || str[j] == '{' || str[j] == '(' || str[j] == '[') {
                stack.push(str[j]);
                continue;
            }
            if (str[j] == '}' && stack.top() == '{') stack.pop();
            else if (str[j] == ']' && stack.top() == '[') stack.pop();
            else if (str[j] == ')' && stack.top() == '(') stack.pop();
        }
        if (stack.size() == 0) answer++;
    }
    return answer;
}