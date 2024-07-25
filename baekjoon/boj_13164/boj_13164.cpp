/**
 * @file boj_13164.cpp
 * @brief 백준 gold5 행복유치원
 * @version 0.1
 * @date 2024-07-25
 * 
 * @copyright Copyright (c) 2024
 * 
 * 흠.. people_cnt - group_cnt 까지만 그룹을 생성하는 것,
 * people[i] - people[i-1]을 통한 차이들을 통해 선택하는 것까지 생각은 했지만 
 * 그냥 이렇게 해도 되는줄은 몰랐음..
 * 
 * 내가 생각했던 예외 상황이
 * 6 2
 * 1 2 3 4 5 6 
 * 상황인데,
 * 이 상황의 경우에는 123을 한 그룹, 456을 한 그룹으로 묶어야 최소 비용을 보장하는데.. 이런 상황의 경우는 어떻게 하는 것인가 싶었다. 
 * 
 * 하지만 people[i] - people[i-1] 라는 것 자체가 두 사람을 선택한 것이고 이후에 추가적인 그룹으로 확장할 때도 그 전 people[i-1] - people[i-2]의 값을 더함으로
 * 연속된 그룹으로 생성이 가능했다.. 
 * 
 * diff를 통한 단순 계산으로 그룹핑이 이렇게 가능하다는 것을 배우게 된 문제이다.
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int people_cnt, group_cnt, answer = 0;
vector<int> people;
priority_queue<int, vector<int>, greater<int> > pq;

int main(){
    cin>>people_cnt>>group_cnt;
    people.resize(people_cnt);
    for(int i=0; i<people_cnt; i++) cin>>people[i];
    for(int i=1; i<people_cnt; i++) pq.push(people[i] - people[i-1]);
    for(int i=0; i<people_cnt - group_cnt; i++) {
        answer += pq.top(); pq.pop();
    }
    cout<<answer;
}