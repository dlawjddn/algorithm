/**
 * @file 전화번호목록_42577.cpp
 * @brief 프로그래머스 lv.2 전화번호 목록
 * @version 0.1
 * @date 2024-09-27
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <string>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

set<string> check;

bool solution(vector<string> phone_book) {
    sort(phone_book.begin(), phone_book.end());
    check.insert(phone_book[0]);
    for(int i=1; i<phone_book.size(); i++) {
        string number = phone_book[i];
        for(int i=0; i<number.size(); i++) {
            string cutted_number = number.substr(0, i+1);
            if (check.find(cutted_number) != check.end()) return false;
        }
        check.insert(number);
    }
    return true;
}