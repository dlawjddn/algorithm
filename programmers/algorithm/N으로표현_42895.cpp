/**
 * @file N으로표현_42895.cpp
 * @brief 프로그래머스 lv.3 N으로 표현
 * @version 0.1
 * @date 2024-10-03
 * 
 * @copyright Copyright (c) 2024
 * 
 * 아 아이디어는 괜찮았는데.. 더 디테일하지 못했다. 
 * 어떤 두 수 a, b가 있을 때 이게 순서에 따라 답이 달라질텐데까지는 생각을 했는데
 * 4를 기준으로 (1,3), (2,2), (3,1) 로 조합하여 모든 경우의 수를 파악한다는 점을 놓쳤다
 * 
 * 단순히 나는 1개 더하는 방법, 괄호로 묶인 2개의 수를 더하는 방법만 고민했었다. 
 * 
 * 흠.. 아쉽구만..
 * 
 * 
 */
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

unordered_map<int, unordered_set<int> > numbers;

int solution(int N, int number) {
    if (N == number) return 1;
    numbers[1].insert(N);
    
    for(int i=2; i<=8; i++) {
        unordered_set<int> now;
        // 숫자가 자릿수만큼 반복되는 경우
        int repeated = stoi(string(i, N+'0'));
        if (repeated == number) return i;
        now.insert(repeated);
        
        // 1부터 i-1까지 조합을 생성
        for(int j=1; j<i; j++) {
            for(auto num1 : numbers[j]) {
                for(auto num2 : numbers[i-j]) {
                    // 덧셈
                    int add = num1 + num2;
                    if (add == number) return i;
                    now.insert(add);
                    
                    // 뺄셈
                    int minus = num1 - num2;
                    if (minus == number) return i;
                    now.insert(minus);
                    
                    // 곱셈
                    int mul = num1 * num2;
                    if (mul == number) return i;
                    now.insert(mul);
                    
                    // 나눗셈
                    if (num2 != 0) {
                        int div = num1 / num2;
                        if (div == number) return i;
                        now.insert(div);
                    }  
                }
            }
        }
        numbers[i] = now;
    }
    
    return -1;
}