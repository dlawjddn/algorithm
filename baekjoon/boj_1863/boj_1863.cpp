#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

vector<pair<int, int> > skylines;

int main() {
    int pos_diff; cin>>pos_diff;
    for(int i=0; i<pos_diff; i++) {
        int pos, h; cin>>pos>>h;
        skylines.push_back({pos, h});
    }
    sort(skylines.begin(), skylines.end());

    stack<int> s;
    int answer = 0;

    for(int i=0; i<skylines.size(); i++) {
        int h = skylines[i].second;
        
        // 현재 변화점보다 낮은 애들 다 빼기 -> 건물의 끝
        while(!s.empty() && h < s.top()) {
            answer++;
            s.pop();
        }

        // 높이가 0인 경우에는 건물이 아니기 때문에 제외
        if (h == 0) continue;

        // 스택이 비어있거나, 현재 탑보다 높은 경우 -> 새로운 건물의 시작
        // 낮은건 이미 다 뺏기 때문에 같거나 높은 경우만 존재, 높이가 같은 경우는 기존 건물의 연장선이기 때문에 추가하지 않음
        if (s.empty() || (!s.empty() && s.top() < h)) s.push(h);
    }

    // 스택에 남아있는 요소 -> 건물이 끝까지 이어져 있는 경우
    while(!s.empty()) {
        answer++;
        s.pop();
    }

    cout<<answer;
}