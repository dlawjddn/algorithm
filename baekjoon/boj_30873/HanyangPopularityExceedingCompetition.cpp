#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int celb_cnt; cin>>celb_cnt;
    int answer = 0;
    for(int i=0; i<celb_cnt; i++) {
        int pop; int fri; cin>>pop>>fri;
        if (abs(pop - answer) <= fri) answer++;
    }
    cout<<answer;
}