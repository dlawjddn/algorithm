/**
 * @file boj_4659.cpp
 * @brief 백준 silver5 비밀번호 발음하기
 * @version 0.1
 * @date 2024-07-14
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>

using namespace std;

bool check_aeiou(char c) {
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
}

bool step1(string s) {
    for (char c : s) {
        if (check_aeiou(c)) return true;
    }
    return false;
}

bool step2(string s) {
    if (s.size() < 3) return true;
    for (int i = 0; i < s.size() - 2; i++) {
        if (check_aeiou(s[i]) && check_aeiou(s[i+1]) && check_aeiou(s[i+2])) return false;
        if (!check_aeiou(s[i]) && !check_aeiou(s[i+1]) && !check_aeiou(s[i+2])) return false;
    }
    return true;
}

bool step3(string s) {
    if (s.size() < 2) return true;
    for (int i = 0; i < s.size() - 1; i++) {
        if (s[i] == s[i+1]) {
            if (s[i] == 'e' || s[i] == 'o') continue;
            return false;
        }
    }
    return true;
}

int main() {
    while (true) {
        string s;
        cin >> s;
        if (s == "end") break;
        cout << "<" << s << ">" << (step1(s) && step2(s) && step3(s) ? " is acceptable.\n" : " is not acceptable.\n");
    }
    return 0;
}
