#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int num_cnt, remove_cnt;
vector<int> numbers;

int main() {
    cin>>num_cnt>>remove_cnt;
    for(int i=0; i<num_cnt; i++) {
        int num; cin>>num;
        numbers.push_back(num);
    }
    int left = 0, right = 0, cnt = 0, answer = 0;
    while(right < num_cnt) {
        if (numbers[right] % 2 == 1) cnt++;
        if (cnt > remove_cnt) {
            if (numbers[left++] % 2 == 1) cnt--;
        }
        answer = max(answer, right - left + 1 - cnt);
        right++;
    }
    cout<<answer;
}