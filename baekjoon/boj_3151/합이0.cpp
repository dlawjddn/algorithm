#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int num_cnt; cin>>num_cnt;
    vector<int> numbers;
    for(int i=0; i<num_cnt; i++) {
        int num; cin>>num;
        numbers.push_back(num);
    }
    sort(numbers.begin(), numbers.end());

    long long answer = 0;
    for(int left = 0; left < numbers.size() - 1; left++) {
        for(int right = left + 1; right < numbers.size(); right++) {
            int left_num = numbers[left];
            int right_num = numbers[right];
            int target = -1 * (left_num + right_num);
            
            int start = lower_bound(numbers.begin() + right + 1, numbers.end(), target) - numbers.begin();
            int end = upper_bound(numbers.begin() + right + 1, numbers.end(), target) - numbers.begin();

            answer += (end - start);
        }
    }
    cout<<answer;
}