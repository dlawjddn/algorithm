#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> devs;
int answer = 0;

int main() {
    int dev_cnt; cin>>dev_cnt;
    for(int i=0; i<dev_cnt; i++) {
        int ability; cin>>ability;
        devs.push_back(ability);
    }
    int left = 0, right = dev_cnt - 1;
    while(left < right) {
        int team = (right - left - 1) * min(devs[left], devs[right]);
        if (answer < team) {
            answer = team;
            left++;
        } else right--;
        answer = max(answer, team);
    }
    cout<<answer;
}