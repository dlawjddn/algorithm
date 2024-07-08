/**
 * @file day1.cpp
 * @brief 엘리스 알고리즘 대회 DAY1 - 목표량
 * @version 0.1
 * @date 2024-07-08
 * 
 * @copyright Copyright (c) 2024
 * 
 * 
 * 
시간 제한: 1초
엘리스 토끼는 목표량을 정해 수학 문제를 열심히 풉니다. 목표량은 정수입니다.

내일 풀 수학 문제의 개수는 오늘 푼 문제 개수의 수와 숫자의 구성이 같으면서, 오늘 푼 문제 개수의 수보다 큰 수 중 가장 작은 수입니다.

예를 들어, 오늘 67문제를 풀었으면 다음 날 76문제를 풉니다.

오늘 푼 문제의 개수를 줬을 때 다음날 풀 문제의 개수를 출력하는 프로그램을 작성하세요.


지시사항
입력
첫 번째 줄에 오늘 푼 문제의 개수인 자연수 N을 입력합니다.


1≤N≤999999


정답이 반드시 있는 경우만 입력값으로 주어집니다.
출력
다음날 풀 문제의 개수를 출력합니다.
입력 예시
364
Copy
출력 예시
436
Copy

main.cpp
C++ (GCC 11.3)

* 
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int origin;
vector<int> numbers;

int main(){
    cin>>origin;
    int copy = origin;
    while(copy > 0) {
        numbers.push_back(copy % 10);
        copy /= 10;
    }
    sort(numbers.begin(), numbers.end());
    do {
        int next = 0;
        for(auto n : numbers) 
            next = next * 10 + n;
        if (next > origin) {
            cout<<next;
            break;
        }
    }while(next_permutation(numbers.begin(), numbers.end()));
}