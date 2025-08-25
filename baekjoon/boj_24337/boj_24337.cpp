#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int building_cnt; cin>>building_cnt;
    int left, right; cin>>left>>right;

    if (left + right - 1 > building_cnt) {
        cout<<-1;
        return 0;
    }

    vector<int> answer;
    int max_height = max(left, right);

    for(int i=1; i<left; i++) answer.push_back(i);
    answer.push_back(max_height);
    for(int i=right - 1; i>=1; i--) answer.push_back(i);

    int remain = building_cnt - (int)answer.size();

    if (left == 1) {
        answer.insert(answer.begin() + 1, remain, 1);
    } else answer.insert(answer.begin(), remain, 1);

    for(int i=0; i<answer.size(); i++) cout<<answer[i]<<' ';
}