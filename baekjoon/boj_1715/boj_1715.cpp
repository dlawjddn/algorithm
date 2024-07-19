/**
 * @file boj_1715.cpp
 * @brief 백준 gold4 카드 정렬하기
 * @version 0.1
 * @date 2024-07-19
 * 
 * @copyright Copyright (c) 2024
 * 
 * 이미 합쳐진 카드가 다시 비교 대상이 된다는 점을 유의하기... 흠.. 아쉽구만..
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

priority_queue<int, vector<int>, greater<int> > pq;

int main(){
    int answer = 0;
    int arr_size; cin>>arr_size;
    for(int i=0; i<arr_size; i++) {
        int num; cin>>num;
        pq.push(num);
    }
    while(pq.size() > 1) { 
        int num1 = pq.top(); pq.pop();
        int num2 = pq.top(); pq.pop();
        answer += (num1 + num2);
        pq.push(num1 + num2);
    }
    cout<<answer;
}