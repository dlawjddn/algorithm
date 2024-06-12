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