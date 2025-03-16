#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;

int main() {
    int len, del_cnt; cin>>len>>del_cnt;
    string num; cin>>num;
    stack<int> s;

    for(int i=0; i<num.size(); i++) {
        int n = num[i] - '0';
        while(!s.empty() && del_cnt > 0 && s.top() < n) {
            s.pop();
            del_cnt--;
        }
        s.push(n);
    }

    while(del_cnt > 0) {
        s.pop();
        del_cnt--;
    }

    string answer = "";
    while(!s.empty()) {
        answer += s.top() + '0';
        s.pop();
    }

    reverse(answer.begin(), answer.end());
    cout<<answer;
}