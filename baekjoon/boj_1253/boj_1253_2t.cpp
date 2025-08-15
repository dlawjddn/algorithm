#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int cnt; cin>>cnt;
    vector<int> nums;

    for(int i=0; i<cnt; i++) {
        int num; cin>>num;
        nums.push_back(num);
    }
    sort(nums.begin(), nums.end());

    int answer = 0;
    for(int i=0; i<nums.size(); i++) {
        int left = 0, right = nums.size() - 1;
        while(left < right) {
            // 서로 다른 수를 선택하기
            if (left == i) {
                left++;
                continue;
            }
            if (right == i) {
                right--;
                continue;
            }

            int sum = nums[left] + nums[right];
            if (sum == nums[i]) {
                answer++;
                break;
            }
            else if (nums[i] < sum) right--;
            else left++;
        }
    }
    cout<<answer;
}