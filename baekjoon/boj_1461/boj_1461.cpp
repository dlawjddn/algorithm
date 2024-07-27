/**
 * @file boj_1461.cpp
 * @brief 백준 gold4 도서관
 * @version 0.1
 * @date 2024-07-27
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct Compare{
    bool operator()(int a, int b) {
        return a > b;
    }
};
int place_cnt, carry_cnt, answer = 0;
vector<int> under_zero;
vector<int> over_zero;
priority_queue<int, vector<int>, greater<int> > pq;

void print_vector() {
    for(int i=0; i<under_zero.size(); i++) cout<<under_zero[i]<<" ";
    cout<<"\n";
    for(int i=0; i<over_zero.size(); i++) cout<<over_zero[i]<<" ";
    cout<<"\n";
}

int main(){
    cin>>place_cnt>>carry_cnt;
    for(int i=0; i<place_cnt; i++) {
        int place; cin>>place;
        if (place < 0) under_zero.push_back(-place);
        else over_zero.push_back(place);
    }
    sort(under_zero.begin(), under_zero.end(), Compare());
    sort(over_zero.begin(), over_zero.end(), Compare());
    for(int i=0; i<under_zero.size(); i+=carry_cnt) pq.push(under_zero[i]);
    for(int i=0; i<over_zero.size(); i+=carry_cnt) pq.push(over_zero[i]);
    while(!pq.empty()) {
        int dist = pq.top(); pq.pop();
        answer += (pq.empty() ? dist : dist * 2);
    }
    cout<<answer;
}