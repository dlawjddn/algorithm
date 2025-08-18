#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

int cnt = 0;
vector<int> numbers;
unordered_map<int, bool> checked;

int main() {
    cin>>cnt;
    for(int i=0; i<cnt; i++) {
        int num; cin>>num;
        numbers.push_back(num);
    }

    int limit = 0;
    long answer = 0;
    for(int start=0; start<numbers.size(); start++) {
        while(limit < numbers.size()) {
            if (checked.find(numbers[limit]) == checked.end()) {
                checked[numbers[limit++]] = true;
            } else break;
        }
        answer += (long) checked.size();
        checked.erase(numbers[start]);
    }
    cout<<answer;
}