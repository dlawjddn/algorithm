#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

int dday, deposit_cnt;
vector<int> days;

int main() {
    cin>>dday>>deposit_cnt;
    for(int i=0; i<dday; i++) {
        int cost; cin>>cost;
        days.push_back(cost);
    }
    int max_cost = *max_element(days.begin(), days.end());
    int left = max_cost;
    int right = accumulate(days.begin(), days.end(), 0);
    int answer = right;
    while(left <= right) {
        int mid = (left + right) / 2;
        int money = mid;
        int cnt = 1;
        for(int i=0; i<days.size(); i++) {
            if (money >= days[i]) {
                money -= days[i];
            } else {
                cnt++;
                money = (mid - days[i]);
            }
        }
        if (cnt > deposit_cnt) {
            left = mid + 1;
        } else {
            right = mid - 1;
            answer = min(answer, mid);
        }
    }
    cout<<answer;
}