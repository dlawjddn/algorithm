/**
 * @file 테이블해시함수_147354.cpp
 * @brief 프로그래머스 lv.2 테이블 해시 함수
 * @version 0.1
 * @date 2024-09-23
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int standard;

struct Compare {
    bool operator()(const vector<int>& arr1, const vector<int>& arr2) const {
        if (arr1[standard] == arr2[standard]) {
            return arr1[0] > arr2[0];
        }
        return arr1[standard] < arr2[standard]; 
    }
};

int solution(vector<vector<int>> data, int col, int row_begin, int row_end) {
    int answer = 0;
    standard = col-1;
    sort(data.begin(), data.end(), Compare());
    for(int i=row_begin-1; i<row_end; i++) {
        int div = i+1;
        int sum = 0;
        for(int j=0; j<data[i].size(); j++) {
            sum += data[i][j] % div;
        }
        answer ^= sum;
    }
    return answer;
}