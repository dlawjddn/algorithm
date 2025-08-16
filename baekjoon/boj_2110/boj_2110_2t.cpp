#include <iostream>
#include <vector>
#include <algorithm>

#define INF 2000000001

using namespace std;

int house_cnt, wifi_cnt;
vector<int> houses;

int main() {
    cin>>house_cnt>>wifi_cnt;
    for(int i=0; i<house_cnt; i++) {
        int house; cin>>house;
        houses.push_back(house);
    }
    sort(houses.begin(), houses.end());

    int answer = 0;
    int left = 1, right = houses.back() - houses.front();
    while(left <= right) {
        int mid = (left + right) / 2;
        int cnt = 1, before_pos = houses.front();
        for(int i=1; i<houses.size(); i++) {
            int diff = houses[i] - before_pos;
            if (diff >= mid) {
                before_pos = houses[i];
                cnt++;
            }
        }
        if (cnt < wifi_cnt) right = mid - 1;
        else {
            left = mid + 1;
            answer = mid;
            continue;
        }
    }
    cout<<answer;
}