/**
 * @file 디스크컨트롤러_42627.cpp
 * @brief 프로그래머스 lv.3 디스크 컨트롤러
 * @version 0.1
 * @date 2024-08-19
 * 
 * @copyright Copyright (c) 2024
 * 
 * 현재 시간보다 시작 시간이 빠른 애들 모두 pq.push(); (pq는 작업 시간이 작은 순으로 정렬되는 상태)
 * 그리고 현재 pq에 들어간 작업들은 모두 당장 시작해서 종료가 가능한 애들 -> 종료까지 바로 해야한다.
 * 따라서 가장 빠른 작업 하나만 마무리 짓는다. 
 * 
 * 이때 pq에 들어간 요소가 없는 경우에는 현재 시간이 작업이 들어오는 시간보다 작다는 의미임으로, 현재 시간을 가장 빠른 작업으로 맞춰줘야함..
 * 
 * 거의 다 생각했는데.. 다시 풀어보도록 하자 ㅅㅂ..
 * 
 */
#include <string>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

vector<pair<int, int> > works;
priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;

int solution(vector<vector<int>> jobs) {
    int idx = 0, now_time = 0;
    int answer = 0;
    for(auto job : jobs) {
        works.push_back({job[0], job[1]});
    }
    sort(works.begin(), works.end());
    while(idx < works.size() || !pq.empty()) {
        while(idx < works.size() && works[idx].first <= now_time) {
            pq.push({works[idx].second, works[idx].first});
            idx++;
        }
        if (pq.empty()) {
            now_time = works[idx].first;
            continue;
        }
        auto[process, start] = pq.top(); pq.pop();
        int wait = now_time - start;
        answer += (wait + process);
        now_time += process;
    }
    return answer / jobs.size();
}