#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int main() {
    int test_case; cin>>test_case;
    for(int t=0; t<test_case; t++) {
        int chapter_cnt; cin>>chapter_cnt;
        long long total_cost = 0;
        priority_queue<long long ,vector<long long>, greater<long long> > pq;
        for(int i=0; i<chapter_cnt; i++) {
            long long chapter; cin>>chapter;
            pq.push(chapter);
        }
        while(pq.size() > 1) {
            long long chapter1 = pq.top(); pq.pop();
            long long chapter2 = pq.top(); pq.pop();
            long long cost = chapter1 + chapter2;

            total_cost += cost;
            pq.push(chapter1 + chapter2);
        }
        //total_cost += pq.top(); pq.pop();
        cout<<total_cost<<"\n";
    }
}