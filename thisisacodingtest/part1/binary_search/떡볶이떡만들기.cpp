#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int cnt, target;
vector<int> a;

int main() {
    cin>>cnt>>target;
    a.resize(cnt);
    for(int i=0; i<cnt; i++) cin>>a[i];
    sort(a.begin(), a.end());
    int left = a[0], right = a.back(), answer = 0;
    while(left <= right) {
        int mid = (left + right) / 2;
        long long sum = 0;
        for(int i=0; i<cnt; i++) {
            if (a[i] > mid) sum += (a[i] - mid);
        }
        if (sum >= target) {
            answer = max(answer, mid);
            left = mid + 1;
        } else right = mid - 1;
    }
    cout<<answer;
}