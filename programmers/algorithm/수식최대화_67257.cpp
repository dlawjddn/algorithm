/**
 * @file 수식최대화_67257.cpp
 * @brief 프로그래머스 lv.2 2020 카카오 인턴십 수식 최대화
 * @version 0.1
 * @date 2024-08-17
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

vector<vector<int>> priorities = {
    {0, 1, 2},
    {0, 2, 1},
    {1, 2, 0},
    {1, 0, 2},
    {2, 0, 1},
    {2, 1, 0}  // 잘못된 우선순위를 올바르게 수정
};
vector<int> operators;
vector<long long> numbers;

int convert_operator(char oper) {
    if (oper == '-') return 0;
    else if (oper == '+') return 1;
    return 2;
}

void split(string origin) {
    operators.clear();  // 벡터 초기화
    numbers.clear();    // 벡터 초기화

    string number = "";
    for (int i = 0; i < origin.size(); i++) {
        if (isdigit(origin[i])) {
            number += origin[i];
        } else {
            operators.push_back(convert_operator(origin[i]));
            numbers.push_back(stoll(number));
            number = "";
        }
    }
    numbers.push_back(stoll(number));
}

long long calculate(long long left, long long right, int oper) {
    if (oper == 0) return left - right;
    else if (oper == 1) return left + right;
    return left * right;
}

long long solution(string expression) {
    long long answer = 0;
    split(expression);
    
    for (auto p : priorities) {
        vector<int> temp_operators = operators;  // 원본을 유지하기 위해 복사본 생성
        vector<long long> temp_numbers = numbers;  // 원본을 유지하기 위해 복사본 생성
        
        for (int i = 0; i < p.size(); i++) {
            for (int j = 0; j < temp_operators.size(); j++) {
                if (p[i] == temp_operators[j]) {
                    long long result = calculate(temp_numbers[j], temp_numbers[j + 1], p[i]);
                    temp_numbers[j] = result;
                    temp_numbers.erase(temp_numbers.begin() + j + 1);
                    temp_operators.erase(temp_operators.begin() + j);
                    j--;
                }
            }
        }
        answer = max(answer, abs(temp_numbers[0]));  // 최종 결과의 절대값이 최대가 되는 것을 반환
    }
    
    return answer;
}
