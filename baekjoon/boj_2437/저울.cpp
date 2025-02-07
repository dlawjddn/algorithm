#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int num_cnt; cin>>num_cnt;
    vector<int> numbers;
    for(int i=0; i<num_cnt; i++) {
        int num; cin>>num;
        numbers.push_back(num);
    }
    sort(numbers.begin(), numbers.end());

    int answer = 1;

    for(int i=0; i<numbers.size(); i++) {
        if (answer < numbers[i]) {
            //cout<<answer;
            break;
        }
        answer += numbers[i];
    }
    cout<<answer;
}