#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

int main() {
    string origin, bomb; cin>>origin>>bomb;
    stack<char> s;
    int cnt = 0;
    for(int i=0; i<origin.size(); i++) {
        s.push(origin[i]);
        if(!s.empty() && s.top() == bomb.back()) {
            int idx = bomb.size() - 1;
            stack<char> temp;
            while(idx >= 0 && !s.empty()) {
                if (bomb[idx] == s.top()) {
                    temp.push(s.top()); s.pop();
                } else break;
                idx--;
            }
            if (idx != -1) {
                while(!temp.empty()) {
                    s.push(temp.top()); temp.pop();
                }
            }
        }
    }
    if (s.empty()) cout<<"FRULA";
    else {
        string answer = "";
        while(!s.empty()) {
            answer += s.top(); s.pop();
        }
        reverse(answer.begin(), answer.end());
        cout<<answer;
    }
}