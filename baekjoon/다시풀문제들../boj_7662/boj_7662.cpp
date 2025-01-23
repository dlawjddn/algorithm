#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_map>
#include <climits>

using namespace std;

void sync_max(priority_queue<pair<int, int>>& pq, unordered_map<int, bool>& is_valid) {
    while (!pq.empty() && !is_valid[pq.top().second]) {
        pq.pop();
    }
}

void sync_min(priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>>& pq, unordered_map<int, bool>& is_valid) {
    while (!pq.empty() && !is_valid[pq.top().second]) {
        pq.pop();
    }
}

int main() {
    int test_case; cin>>test_case;
    for(int t=0; t<test_case; t++) {
        int order_cnt; cin>>order_cnt;
        priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > min_queue;
        priority_queue<pair<int, int>, vector<pair<int, int> >, less<pair<int, int> > > max_queue;
        unordered_map<int, bool> checker;
        for(int i=0; i<order_cnt; i++) {
            char order; cin>>order;
            int num; cin>>num;
            if (order == 'I') {
                min_queue.push({num, i});
                max_queue.push({num, i});
                checker[i] = true;
                continue;
            } else {
                if (num == -1) {
                    // 최솟값을 삭제
                    sync_min(min_queue, checker);
                    if (!min_queue.empty()) {
                        checker[min_queue.top().second] = false;
                        min_queue.pop();
                    }
                } else {
                    // 최댓값을 삭제
                    sync_max(max_queue, checker);
                    if (!max_queue.empty()) {
                        checker[max_queue.top().second] = false;
                        max_queue.pop();
                    }
                }
            }
        }
        sync_max(max_queue, checker);
        sync_min(min_queue, checker);
        if (min_queue.empty() || max_queue.empty()) cout<<"EMPTY\n";
        else cout<<max_queue.top().first<<" "<<min_queue.top().first<<"\n";
    }
}