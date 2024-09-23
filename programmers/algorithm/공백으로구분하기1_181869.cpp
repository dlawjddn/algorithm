/**
 * @file 공백으로구분하기1_181869.cpp
 * @brief 프로그래머스 lv.0 공백으로 구분하기 1
 * @version 0.1
 * @date 2024-09-23
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <string>
#include <vector>
#include <iostream>
#include <sstream>

using namespace std;

vector<string> split(string origin) {
    vector<string> result;
    string token;
    istringstream token_stream(origin);
    while(getline(token_stream, token, ' ')) {
        result.push_back(token);
    }
    return result;
}

vector<string> solution(string my_string) {
    return split(my_string);
}