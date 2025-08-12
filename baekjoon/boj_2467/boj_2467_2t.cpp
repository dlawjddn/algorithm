#include <iostream>
#include <vector>
#include <algorithm>

#define INF 2000000001

using namespace std;

int cnt;
vector<int> nums;

int main() {
    cin>>cnt;
    for(int i=0; i<cnt; i++) {
        int num; cin>>num;
        nums.push_back(num);
    }

    int left = 0, right = cnt - 1;
    int answer_sum = INF, answer_left = 0, answer_right = cnt - 1; 
    while(left < right) {
        int sum = nums[left] + nums[right];
        if (sum == 0) {
            answer_sum = sum;
            answer_left = left;
            answer_right = right;
            break;
        }
        else if (sum > 0) {
            if (abs(answer_sum) > abs(sum)) {
                answer_sum = sum;
                answer_left = left;
                answer_right = right;
            }
            right--;
        }
        else {
            if (abs(answer_sum) > abs(sum)) {
                answer_sum = sum;
                answer_left = left;
                answer_right = right;
            }   
            left++;
        }
    }
    cout<<nums[answer_left]<<' '<<nums[answer_right];
}