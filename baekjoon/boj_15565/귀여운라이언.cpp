#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int doll_cnt, lion_cnt; cin>>doll_cnt>>lion_cnt;
    vector<int> dolls;
    for(int i=0; i<doll_cnt; i++) {
        int doll; cin>>doll;
        dolls.push_back(doll);
    }
    int left = 0, right = 0;
    int cnt = 0;
    int answer = 987654321;

    while(right < doll_cnt) {
        cnt += (dolls[right] == 1) ? 1 : 0;
        right++;
        while(cnt >= lion_cnt) {
            answer = min(answer, right - left);
            cnt -= (dolls[left] == 1) ? 1 : 0;
            left++;
        }
    }

    if (answer == 987654321) cout<<-1;
    else cout<<answer;
}