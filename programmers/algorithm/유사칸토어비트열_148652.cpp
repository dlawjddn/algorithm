/**
 * @file 유사칸토어비트열_148652.cpp
 * @brief 프로그래머스 lv.2 유사 칸토어 비트열
 * @version 0.1
 * @date 2024-08-14
 * 
 * @copyright Copyright (c) 2024
 * 
 * 재귀적으로 나눌 때, 가운데가 0이 된다는 점은 생각보다 빠르게 파악했지만, 이상한 곳에서 삽질을 많이한 문제..
 * 나머지를 계산할 때는 0-Based number로 계산하자..
 * 
 */
#include <string>
#include <vector>
#include <cmath>
#include <iostream>
using namespace std;

bool divide_five(long long num, int n) {
    if (n == 0) return true;
    long long divider = pow(5, n-1);
    long long div = num / divider; // 몫
    long long mod = num % divider; // 나머지
    
    if (div == 2) {
        return false;
    }
    return divide_five(mod, n-1);
}

int solution(int n, long long l, long long r) {
    int answer = 0;
    for(long long i=l-1; i<r; i++) {
        if (divide_five(i, n)) {
            //cout<<i<<" ";
            answer++;
        }
    }
    return answer;
}