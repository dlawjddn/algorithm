#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int line_cnt;
vector<pair<int, int> > lines;
priority_queue<int, vector<int>, greater<int> > pq;

bool compare(pair<int, int> p1, pair<int, int> p2) {
    if (p1.first == p2.first) return p1.second < p2.second;
    return p1.first < p2.first;
}

int main() {
    cin>>line_cnt;
    for(int i=0; i<line_cnt; i++) {
        int start, end; cin>>start>>end;
        lines.push_back({start, end});
    }
    sort(lines.begin(), lines.end(), compare);

    int answer = 0;
    for(auto[start, end] : lines) {
        while(!pq.empty() && pq.top() <= start) { // 현재 선택한 선분의 시작점보다 이전의 끝점이 작거나 같다면(범위에 속하지 않으면)
            pq.pop(); // 지금의 선분과 겹쳐질 수 없는 요소를 제거
        }
        pq.push(end);
        answer = max(answer, (int)pq.size()); // pq에 존재하는 요소는 현재 선택한 선분을 포함해서 선택할 수 있는 최대 선분의 길이
    }
    cout<<answer;
}