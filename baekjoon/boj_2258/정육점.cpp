#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int meet_cnt, target, total_size = 0;
long long answer = 2147483648;
vector<pair<int, int> > infos;

bool compare(pair<int, int> p1, pair<int, int> p2) {
    if (p1.second == p2.second) return p1.first > p2.first;
    return p1.second < p2.second;
}

int main() {
    cin>>meet_cnt>>target;
    for(int i=0; i<meet_cnt; i++) {
        int size, price; cin>>size>>price;
        infos.push_back({size, price});
    }
    sort(infos.begin(), infos.end(), compare);
    int idx = 0;
    while(idx < infos.size()) {
        auto[now_size, now_price] = infos[idx];
        if (total_size + now_size >= target) {
            answer = min(answer, (long long)now_price);
        }

        int nidx = idx + 1;
        int same_sum_size = 0;
        int same_sum_price = 0;
        while(nidx < infos.size() && infos[idx].second == infos[nidx].second) {
            same_sum_size += infos[nidx].first;
            same_sum_price += infos[nidx].second;
            if (total_size + same_sum_size + now_size >= target) {
                answer = min(answer, (long long)(same_sum_price + now_price));
            }
            nidx++;
        }
        total_size += (now_size + same_sum_size);
        idx = nidx;
    }
    cout<<((answer == 2147483648) ? -1 : answer);

}