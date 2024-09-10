/**
 * @file 숫자카드나누기_135807.cpp
 * @brief 프로그래머스 lv.2 숫자 카드 나누기
 * @version 0.1
 * @date 2024-09-10
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <iostream>

using namespace std;

vector<int> get_division(int number) {
    set<int> sorted_result;
    for(int i=1; i*i<=number; i++) {
        if (number % i != 0) continue;
        sorted_result.insert(i);
        sorted_result.insert(number / i);
    }
    return vector<int>(sorted_result.begin(), sorted_result.end());
}

int gcd(vector<int> arr) {
    int result = arr[0];
    for(int i=1; i<arr.size(); i++) {
        result = __gcd(result, arr[i]);
    }
    return result;
}

int solution(vector<int> arrayA, vector<int> arrayB) {
    int answer = 0;
    vector<int> divisorA = get_division(gcd(arrayA));
    for(int i=0; i<divisorA.size(); i++) {
        bool success = true;
        for(int j=0; j<arrayB.size(); j++) {
            if (arrayB[j] % divisorA[i] == 0) {
                success = false;
                break;
            }
        }
        if (success) answer = max(answer, divisorA[i]);
    }
    vector<int> divisorB = get_division(gcd(arrayB));
    for(int i=0; i<divisorB.size(); i++) {
        bool success = true;
        for(int j=0; j<arrayA.size(); j++) {
            if (arrayA[j] % divisorB[i] == 0) {
                success = false;
                break;
            }
        }
        if (success) answer = max(answer, divisorB[i]);
    }
    
    return answer;
}