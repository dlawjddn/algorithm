#include <iostream>
#include <vector>
#include <algorithm>

#define INF 987654321

using namespace std;

int trap_cnt, height, answer_value = INF, answer_cnt = 0;
vector<int> traps; // 높이에 따른 장애물의 개수

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin>>trap_cnt>>height;
    traps.resize(height + 1, 0);
    for(int i=0; i<trap_cnt; i++) {
        int h; cin>>h;
        if (i % 2 == 0) {
            // 바닥에서부터 높이
            traps[0]++;
            traps[h]--;
        } else {
            traps[height - h]++;
            traps[height]--;
        }
    }
    for(int i=1; i<traps.size(); i++) {
        traps[i] += traps[i-1];
    }
    traps.pop_back();
    for(int i=0; i<traps.size(); i++) {
        if (traps[i] < answer_value) {
            answer_value = traps[i];
            answer_cnt = 1;
        }
        else if (traps[i] == answer_value) answer_cnt++;
    }
    cout<<answer_value<<" "<<answer_cnt;
}