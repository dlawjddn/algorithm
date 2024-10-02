/**
 * @file 숫자문자열과영단어_81301.cpp
 * @brief 프로그래머스 lv.1 2021 카카오 인턴십 숫자 문자열과 영단어
 * @version 0.1
 * @date 2024-10-02
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

unordered_map<string, string> converter;

void init() {
    converter["zero"] = "0";
    converter["one"] = "1";
    converter["two"] = "2";
    converter["three"] = "3";
    converter["four"] = "4";
    converter["five"] = "5";
    converter["six"] = "6";
    converter["seven"] = "7";
    converter["eight"] = "8";
    converter["nine"] = "9";
}

int solution(string s) {
    string temp = "";
    string answer = "";
    init();
    for(int i=0; i<s.size(); i++) {
        if (s[i] >= '0' && s[i] <= '9') {
            if (temp != "") {
                answer += converter[temp];
                temp = "";
            }
            answer += s[i];
            continue;
        }
        temp += s[i];
        if (converter.find(temp) != converter.end()) {
            answer += converter[temp];
            temp = "";
        }
    }
    return stoi(answer);
}