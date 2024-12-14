#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_map>

using namespace std;

int idx, mul[3] = {2,3,5};
unordered_map<long long, bool> ugly_number;

long long solve() {
    priority_queue<long long, vector<long long>, greater<long long> > pq;
    pq.push(1);
    ugly_number[1] = true;
    int cnt = 0;
    while(!pq.empty()) {
        long long num = pq.top(); pq.pop();
        cnt++;
        if (cnt == idx) {
            return num;
        }
        for(int d=0; d<3; d++) {
            long long nnum = num * mul[d];
            if (ugly_number.find(nnum) != ugly_number.end()) continue;
            pq.push(nnum);
            ugly_number[nnum] = true;
        }
    }
}

int main() {
    cin>>idx;
    cout<<solve();
}