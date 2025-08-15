#include <iostream>
#include <vector>
#include <algorithm>

#define INF 987654321

using namespace std;

int cnt, target;
vector<int> nums;

int main() {
    cin>>cnt>>target;
    for(int i=0; i<cnt; i++) {
        int num; cin>>num;
        nums.push_back(num);
    }
    int answer = INF;
    int left = 0, right = 0, sum = 0;
    while(left <= right && right <= cnt) {
        if (sum < target) {
            sum += nums[right++];
            continue;
        }
        else {
            answer = min(answer, right - left);
            sum -= nums[left++];
            continue;
        }
    }
    cout<<((answer == INF) ? 0 : answer);
}