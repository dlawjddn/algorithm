#include <string>
#include <vector>
#include <iostream>
#include <stack>

using namespace std;

pair<string, string> div_str(string str) {
    int open_cnt = 0, close_cnt = 0;
    bool finish = false;
    string u = "", v= "";
    for(int i=0; i<str.size(); i++) {
        (str[i] == '(') ? open_cnt++ : close_cnt++;
        if (finish) {
            v += str[i];
        } else {
            if (open_cnt == close_cnt) finish = true;
            u += str[i];
        }
    }
    return {u, v};
}

bool corrected_str(string str) {
    stack<char> s;
    for(int i=0; i<str.size(); i++) {
        if (str[i] == '(') s.push(str[i]);
        else {
            if (!s.empty() && s.top() == '(') s.pop();
            else return false;
        }
    }
    return (s.empty() ? true : false);
}

string delete_reverse(string str) {
    string result = "";
    for(int i=1; i<str.size() - 1; i++) {
        result += (str[i] == '(') ? ')' : '(';
    }
    return result;
}

string dfs(string str) {
    if (str == "") return "";
    auto[u, v] = div_str(str);
    if (corrected_str(u))  return u + dfs(v);
    return "(" + dfs(v) + ")" + delete_reverse(u);
}

string solution(string p) {
    return dfs(p);
}