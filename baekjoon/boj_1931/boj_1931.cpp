/**
 * @file boj_1931.cpp
 * @brief 백준 silver1 회의실 배정
 * @version 0.1
 * @date 2024-07-08
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int meeting_cnt;
vector<pair<int, int> > meetings;

int main(){
    cin>>meeting_cnt;
    for(int i=0; i<meeting_cnt; i++) {
        int start, end; cin>>start>>end;
        meetings.push_back(make_pair(end, start));
    }
    sort(meetings.begin(), meetings.end());
    int last_end = 0, cnt = 0;
    for(int i=0; i<meetings.size(); i++) {
        int end = meetings[i].first;
        int start = meetings[i].second;
        if (last_end <= start) {
            cnt++;
            last_end = end;
        }
    }
    cout<<cnt;
}