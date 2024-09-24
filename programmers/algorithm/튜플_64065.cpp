/**
 * @file 튜플_64065.cpp
 * @brief 프로그래머스 lv.2 2019 카카오 인턴십 튜플
 * @version 0.1
 * @date 2024-09-24
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <set>

using namespace std;

set<int> check;

bool compare(vector<int>& v1, vector<int>& v2) {
    return v1.size() < v2.size();
}

vector<int> solution(string s) {
    vector<int> answer;
    vector<vector<int> > tuples;
    vector<int> temp;
    int number = 0;
    for(int i=1; i<s.size()-1; i++) {
        if (s[i] == '{')
            temp = vector<int>();
        else if (s[i] == '}') {
            temp.push_back(number);
            tuples.push_back(temp);
        }
        else if (s[i] == ',') {
            if (number == 0) continue;
            temp.push_back(number);
            number = 0;
        }
        else {
            number *= 10;
            number += (s[i] - '0');
        }
    }
    sort(tuples.begin(), tuples.end(), compare);
    for(auto tuple : tuples) {
        for(auto num : tuple) {
            if (check.find(num) == check.end()) { // 기존에 없던 숫자
                check.insert(num);
                answer.push_back(num);
            }
        }
    }
    return answer;
}