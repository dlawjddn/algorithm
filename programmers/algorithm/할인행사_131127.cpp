/**
 * @file 할인행사_131127.cpp
 * @brief 프로그래머스 lv.2 할인행사
 * @version 0.1
 * @date 2024-09-27
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

unordered_map<string, int> wants;

int solution(vector<string> want, vector<int> number, vector<string> discount) {
    int answer = 0;
    for(int i=0; i<want.size(); i++) {
        wants[want[i]] = number[i];
    }
    for(int i=0; i<=discount.size() - 10; i++) {
        unordered_map<string, int> check;
        for(int j=i; j<i+10; j++) {
             check[discount[j]]++;
        }
        bool success = true;
        for(int k=0; k<want.size(); k++) {
            if (wants[want[k]] != check[want[k]]) {
                success = false;
                break;
            }
        }
        if (success) answer++;
    }
    return answer;
}