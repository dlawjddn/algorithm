/**
 * @file 야근지수_12927.cpp
 * @brief 프로그래머스 lv3. 야근 지수
 * @version 0.1
 * @date 2024-06-20
 * 
 * @copyright Copyright (c) 2024
 * 
 * 너무 아쉽다 다 생각했는데 54321이라는 야근 시간이 주어질 때 -> 4 3 1 1 1 이렇게 야근을 해야하는 것까지 파악했지만
 * 이걸 어떻게 구현하지라는 생각이 먼저 들어서 정답을 확인하고 자괴감이 들었다..
 * 
 * 그렇다 지금 생각하면 큰 놈부터 1이 될때까지 빼주고, 0이 되면 queue에 삽입하지 않는 방법인건데... 너무 당연한 생각이지만 생각이 안 났다..
 * 좀 힘드네 ㅠ 힝
 */
#include <string>
#include <vector>
#include <queue>
#include <iostream>
#include <cmath>

using namespace std;

long long solution(int n, vector<int> works) {
    long long answer = 0;
    priority_queue<int> pq;
    for(auto work : works)
        pq.push(work);
    while(n-- && !pq.empty()) {
        int work = pq.top(); pq.pop();
        if (work == 1) continue;
        pq.push(work - 1);
    }
    while(!pq.empty()){
        answer += pow(pq.top(), 2);
        pq.pop();
    }
    return answer;
}
/**
 * @file 야근지수_12927.cpp
 * @brief 프로그래머스 lv.3 야근지수
 * @version 0.1
 * @date 2024-08-17
 * 
 * @copyright Copyright (c) 2024
 * 
 * 저번에 못 푼 문제를 풀었다 야호~
 * 
 */

#include <string>
#include <vector>
#include <queue>

using namespace std;

priority_queue<int, vector<int>, less<int> > pq;

long long solution(int n, vector<int> works) {
    long long answer = 0;
    for(int i=0; i<works.size(); i++) {
        pq.push(works[i]);
    }
    for(int i=0; i<n; i++) {
        if (pq.empty()) break;
        int rest_work = pq.top(); pq.pop();
        if (rest_work == 0) continue;
        pq.push(rest_work - 1);
    }
    while(!pq.empty()) {
        long long work = (long long)pq.top(); pq.pop();
        answer += (work * work);
    }
    return answer;
}
