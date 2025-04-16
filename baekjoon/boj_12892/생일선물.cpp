#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int gift_cnt, diff; cin>>gift_cnt>>diff;
    vector<pair<int, int> > gifts;
    for(int i=0; i<gift_cnt; i++) {
        int price, value; cin>>price>>value;
        gifts.push_back({price, value});
    }
    sort(gifts.begin(), gifts.end());

    int left = 0, right = 0;
    long long sum = 0;
    long long answer = 0;

    while(right < gift_cnt) {
        if (left < gift_cnt && (gifts[right].first - gifts[left].first) < diff) {
            sum += gifts[right].second;
            answer = max(answer, sum);
            right++;
        }
        while((gifts[right].first - gifts[left].first) >= diff) {
            sum -= gifts[left].second;
            left++;
        }
    }
    cout<<answer;
}