/**
 * @file boj_1374.cpp
 * @brief 백준 gold5 강의실
 * @version 0.1
 * @date 2024-08-02
 * 
 * @copyright Copyright (c) 2024
 * 
 * 그리디의 정석같은 문제.. 그래도 이건 빠르게, 한번에 푼다..
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct Compare {
    bool operator()(pair<int, int> p1, pair<int, int> p2) {
        if (p1.first == p2.first) {
            return p1.second < p2.second;
        }
        return p1.first < p2.first;
    }
};
int class_cnt;
vector<pair<int, int> > classes;
priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;

int main(){
    cin>>class_cnt;
    for(int i=0; i<class_cnt; i++) {
        int class_num, start, end; cin>>class_num>>start>>end;
        classes.push_back({start, end});
    }
    sort(classes.begin(), classes.end(), Compare());
    for(int i=0; i<classes.size(); i++) {
        if (pq.empty() || pq.top().first > classes[i].first) {
            pq.push({classes[i].second, classes[i].first});
            continue;
        }
        pq.pop();
        pq.push({classes[i].second, classes[i].first});
    }
    cout<<pq.size();
}