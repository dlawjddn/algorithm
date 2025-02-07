#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

int assignment_cnt;
vector<pair<int, int> > assignments;
vector<int> result(1000, 0);

bool compare(pair<int, int> p1, pair<int, int> p2) {
    if (p1.second == p2.second) {
        return p1.first < p2.first;
    }return p1.second > p2.second;
}

int main() {
    cin>>assignment_cnt;
    for(int i=0; i<assignment_cnt; i++) {
        int end_day, score; cin>>end_day>>score;
        assignments.push_back({end_day, score});
    }
    sort(assignments.begin(), assignments.end(), compare);

    for(int i=0; i<assignment_cnt; i++) {
        for(int j=assignments[i].first - 1; j>=0; j--) {
            if (result[j] == 0) {
                result[j] = assignments[i].second;
                break;
            }
        }
    }
    cout<<accumulate(result.begin(), result.end(), 0);
}