#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>

using namespace std;
queue<string> q;

int main() {
    bool findout = false;
    string s, t; cin>>s>>t;
    q.push(t);
    while(!q.empty()) {
        string now = q.front(); q.pop();

        if (now == s) {
            findout = true;
            break;
        }

        if (now.back() == 'A') {
            string next = now.substr(0, now.size() - 1);
            if (next.size() < s.size()) continue;
            q.push(next);
        }

        if (now.front() == 'B') {
            string next = now.substr(1, now.size());
            reverse(next.begin(), next.end());
            if (next.size() < s.size()) continue;
            q.push(next);
        }
    }
    cout<<((findout) ? 1 : 0);
}