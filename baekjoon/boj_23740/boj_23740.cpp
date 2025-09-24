#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Info {
    int start, end, cost;
    bool operator<(Info other) const {
        if (start == other.start) return end < other.end;
        return start < other.start;
    }
};
int path_cnt;
vector<Info> paths;

int main() {
    cin>>path_cnt;
    for(int i=0; i<path_cnt; i++) {
        int start, end, cost; cin>>start>>end>>cost;
        paths.push_back({start, end, cost});
    }
    sort(paths.begin(), paths.end());

    vector<Info> answer;
    int left = paths[0].start, right = paths[0].end, min_cost = paths[0].cost;
    for(int i=1; i<paths.size(); i++) {
        auto[start, end, cost] = paths[i];
        if ((left <= start && start <= right) || (left <= end && end <= right)) {
            left = min(left, start);
            right = max(right, end);
            min_cost = min(min_cost, cost);
        }
        else {
            answer.push_back({left, right, min_cost});
            left = start;
            right = end;
            min_cost = cost;
        }
    }
    answer.push_back({left, right, min_cost});
    sort(answer.begin(), answer.end());

    cout<<answer.size()<<'\n';
    for(auto[start, end, cost] : answer) {
        cout<<start<<' '<<end<<' '<<cost<<'\n';
    }
}
