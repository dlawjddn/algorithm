/**
 * @file boj_12764.cpp
 * @brief 백준 gold3 싸지방에 간 준하
 * @version 0.1
 * @date 2024-08-01
 * 
 * @copyright Copyright (c) 2024
 * 
 * 우선순위 큐 두 개 사용하는 것.. 좋은 방향인거 같다 유의하자..!
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int node_cnt;
vector<pair<int, int> > people;
vector<int> answer(100001, 0);
priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
priority_queue<int, vector<int>, greater<int> > empty_seat;

int main(){
    cin>>node_cnt;
    people.resize(node_cnt);
    for(int i=0; i<node_cnt; i++) {
        cin>>people[i].first>>people[i].second;
    }
    sort(people.begin(), people.end());

    int seat_idx = 0;
    for(int i=0; i<people.size(); i++) {
        while(!pq.empty() && pq.top().first <= people[i].first) {
            int seat = pq.top().second; pq.pop();
            empty_seat.push(seat);
        }
        if (empty_seat.empty()) {
            pq.push(make_pair(people[i].second, seat_idx));
            answer[seat_idx++] += 1;
        }
        else {
            int seat = empty_seat.top(); empty_seat.pop();
            pq.push(make_pair(people[i].second, seat));
            answer[seat] += 1;
        }
    }
    cout<<seat_idx<<"\n";
    for(int i=0; i<seat_idx; i++) cout<<answer[i]<<" ";
}