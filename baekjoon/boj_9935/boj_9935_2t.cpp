#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

int main() {
    string origin; cin>>origin;
    string bomb; cin>>bomb;

    stack<char> s;
    for(int i=0; i<origin.size(); i++) {
        s.push(origin[i]);
        if (!s.empty() && s.top() == bomb.back() && s.size() >= bomb.size()) {
            int findout = true;
            vector<char> temp;
            for(int i = bomb.size() - 1; i>=0; i--) {
                temp.push_back(s.top()); s.pop();
                if (temp.back() != bomb[i]) {
                    findout = false;
                    break;
                }
            }
            if (!findout) {
                for(int i=temp.size() - 1; i>=0; i--) {
                    s.push(temp[i]);
                }
            }
        }
    }
    if (s.empty()) {
        cout<<"FRULA\n";
    } else {
        string answer = "";
        while(!s.empty()) {
            answer += s.top(); s.pop();
        }
        reverse(answer.begin(), answer.end());
        cout<<answer;
    }

}