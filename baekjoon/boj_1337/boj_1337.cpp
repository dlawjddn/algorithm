#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

int cnt, answer = 5;
vector<int> numbers;
unordered_map<int, bool> checker;

int main() {
    cin>>cnt;
    for(int i=0; i<cnt; i++) {
        int num; cin>>num;
        numbers.push_back(num);
        checker[num] = true;
    }
    sort(numbers.begin(), numbers.end());

    for(int i=0; i<numbers.size(); i++) {
        int start = numbers[i];
        int cnt = 0;
        for(int j=1; j<5; j++) {
            if (!checker[start + j]) cnt++;
        }
        answer = min(answer, cnt);
    }
    cout<<answer;
}