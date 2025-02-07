#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int holl_cnt, shield_size;

int main() {
    cin>>holl_cnt>>shield_size;
    vector<pair<int, int> > holls;
    for(int i=0; i<holl_cnt; i++) {
        int start, end; cin>>start>>end;
        holls.push_back({start, end});
    }
    sort(holls.begin(), holls.end());

    int pos = 0;
    int answer = 0;
    for(auto holl : holls) {
        int start = max(pos, holl.first);
        int end = holl.second;
        if (end < start) continue;
        int size = end - start;
        int cnt = ((size % shield_size == 0) ? size / shield_size : (size / shield_size) + 1);

        answer += cnt;
        pos = (start + cnt * shield_size);
    }
    cout<<answer;
}