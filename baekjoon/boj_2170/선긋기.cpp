#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool compare(pair<int, int> p1, pair<int, int> p2) {
    if (p1.first == p2.second) return p1.second < p2.second;
    return p1.first < p2.first;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int line_cnt; cin>>line_cnt;
    vector<pair<int, int> > lines;
    for(int i=0; i<line_cnt; i++) {
        int start, end; cin>>start>>end;
        lines.push_back({start, end});
    }
    sort(lines.begin(), lines.end(), compare);

    long long answer = 0;
    pair<int, int> line = lines[0];
    for(int i=1; i<lines.size(); i++) {
        pair<int, int> new_line = lines[i];
        if (line.first <= new_line.first && new_line.first <= line.second) {
            // 구간에 포함되면
            line.first = min(line.first, new_line.first);
            line.second = max(line.second, new_line.second);
        } else {
            //cout<<line.first<<" "<<line.second<<"\n";
            answer += (line.second - line.first);
            line = new_line;
        }
    }
    //cout<<line.first<<" "<<line.second<<"\n";
    answer += (line.second - line.first);
    cout<<answer;
}