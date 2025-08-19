#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

int cnt;
vector<int> heights;
vector<int> left_near, left_cnt;
vector<int> right_near, right_cnt;


int main() {
    cin>>cnt;
    left_near.resize(cnt, -1); left_cnt.resize(cnt, 0);
    right_near.resize(cnt, -1); right_cnt.resize(cnt, 0);
    for(int i=0; i<cnt; i++) {
        int height; cin>>height;
        heights.push_back(height);
    }

    // 1. 특정 빌딩 기준 왼쪽으로 보이는 빌딩 파악하기
    stack<int> s1;
    for(int i=0; i<heights.size(); i++) {
        while (!s1.empty() && heights[s1.top()] <= heights[i]) {
            s1.pop();
        }
        if (!s1.empty()) {
            left_near[i] = s1.top();
            left_cnt[i] = left_cnt[s1.top()] + 1;
        }
        s1.push(i);
    }

    // 2. 특정 빌딩 기준 오른쪽으로 보이는 빌딩 파악하기
    stack<int> s2;
    for(int i=heights.size() - 1; i>=0; i--) {
        while (!s2.empty() && heights[s2.top()] <= heights[i]) {
            s2.pop();
        }
        if (!s2.empty()) {
            right_near[i] = s2.top();
            right_cnt[i] = right_cnt[s2.top()] + 1;
        }
        s2.push(i);
    }

    for(int i=0; i<cnt; i++) {
        int sum = left_cnt[i] + right_cnt[i];
        cout<<sum<<' ';
        int closest;
        if (sum != 0) {
            if (left_near[i] != -1 && right_near[i] != -1) {
                int abs_left = abs(i - left_near[i]);
                int abs_right = abs(i - right_near[i]);
                if (abs_left <= abs_right) closest = left_near[i];
                else closest = right_near[i];
            }
            else if (left_near[i] == -1) closest = right_near[i];
            else if (right_near[i] == -1) closest = left_near[i];
            cout<<closest + 1;
        }
        cout<<'\n';
    }
}