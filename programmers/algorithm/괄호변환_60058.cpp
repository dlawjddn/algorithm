/**
 * @file 괄호변환_60058.cpp
 * @brief 프로그래머스 lv.2 2020 카카오 공채 괄호변환
 * @version 0.1
 * @date 2024-08-15
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <string>
#include <vector>
#include <stack>

using namespace std;

int divide_string(string origin) {
    int cnt_open = 0;
    int cnt_close = 0;
    for(int i=0; i<origin.size(); i++) {
        if (origin[i] == '(') cnt_open++;
        else cnt_close++;
        
        if (cnt_open == cnt_close) break;
    }
    return cnt_open + cnt_close;
}

bool correct_string(string origin) {
    stack<char> s;
    for(int i=0; i<origin.size(); i++) {
        if (origin[i] == '(') s.push(origin[i]);
        else {
            if (s.empty()) return false;
            else s.pop();
        }
    }
    if (s.empty()) return true;
    return false;
}

string erase_reverse(string origin) {
    string result = "";
    for(int i=1; i<origin.size()-1; i++) {
        result += (origin[i] == '(' ? ')' : '(');
    }
    return result;
}

string dfs(string p) {
    if (p.size() == 0) return "";
    
    int cnt = divide_string(p);
    string u = p.substr(0, cnt);
    string v = p.substr(cnt);
    
    if (correct_string(u)) {
        return u + dfs(v);
    } else {
        return "(" + dfs(v) + ")" + erase_reverse(u);
    }
}

string solution(string p) {
    return dfs(p);
}