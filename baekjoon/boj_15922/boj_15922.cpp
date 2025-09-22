#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool compare(const pair<long long, long long>& a,
             const pair<long long, long long>& b) {
    if (a.first != b.first) return a.first < b.first; // 시작점 오름차순
    return a.second > b.second;                       // 시작 같으면 끝점 내림차순
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<pair<long long, long long> > segs;
    segs.reserve(n);

    for (int i = 0; i < n; i++) {
        long long s, e;
        cin >> s >> e;
        if (s > e) swap(s, e);
        segs.push_back({s, e});
    }

    sort(segs.begin(), segs.end(), compare);

    long long answer = 0;
    long long L = segs[0].first;
    long long R = segs[0].second;

    for (int i = 1; i < n; i++) {
        long long s = segs[i].first;
        long long e = segs[i].second;

        if (s <= R) {
            if (e > R) R = e;               // 겹치면 구간 확장
        } else {
            answer += (R - L);              // 끊기면 누적
            L = s; 
            R = e;                          // 새 구간 시작
        }
    }

    answer += (R - L);                       // 마지막 구간 더하기
    cout << answer << '\n';
    return 0;
}
