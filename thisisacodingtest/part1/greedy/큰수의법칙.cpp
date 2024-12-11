#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> numbers;

int main() {
    int total_cnt = 0, plus_cnt=0, limit=0; cin>>total_cnt>>plus_cnt>>limit;
    numbers.resize(total_cnt);
    for(int i=0; i<total_cnt; i++) cin>>numbers[i];
    sort(numbers.rbegin(), numbers.rend());
    int cnt = 0, answer = 0;
    for(int i=0; i<plus_cnt; i++) {
        if (cnt >= limit) {
            answer += numbers[1];
            cnt = 0;
            continue;
        }
        answer += numbers[0];
        cnt += 1;
    }
    cout<<answer;
}