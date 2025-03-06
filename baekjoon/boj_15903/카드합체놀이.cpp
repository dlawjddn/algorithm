#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int main() {
    int card_cnt, mix_cnt; cin>>card_cnt>>mix_cnt;
    priority_queue<long long, vector<long long>, greater<long long> > pq;
    for(int i=0; i<card_cnt; i++) {
        long long card; cin>>card;
        pq.push(card);
    }
    while(mix_cnt > 0) {
        long long first_small = pq.top(); pq.pop();
        long long second_small = pq.top(); pq.pop();
        pq.push(first_small + second_small);
        pq.push(first_small + second_small);
        mix_cnt--;
    }
    long long answer = 0;
    while(!pq.empty()) {
        answer += pq.top(); pq.pop();
    }
    cout<<answer;
}