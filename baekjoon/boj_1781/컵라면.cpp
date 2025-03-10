#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int problem_cnt;
vector<pair<int, int> > problems;
vector<bool> solved;
vector<int> parents;

bool compare(pair<int, int> p1, pair<int, int> p2) {
    if (p1.second == p2.second) return p1.first > p2.first;
    return p1.second > p2.second;
}

int find_parent(int node) {
    if (parents[node] == node) return node;
    return parents[node] = find_parent(parents[node]);
}

void make_union(int node1, int node2) {
    parents[node1] = node2;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>problem_cnt;
    solved.resize(problem_cnt + 1, false);
    for(int i=0; i<problem_cnt; i++) {
        int deadline, ramen; cin>>deadline>>ramen;
        problems.push_back({deadline, ramen});
    }
    sort(problems.begin(), problems.end(), compare);

    for(int i=0; i<=problem_cnt; i++) parents.push_back(i);

    int answer = 0;
    for(int i=0; i<problem_cnt; i++) {
        auto[deadline, ramen] = problems[i];
        int available_day = find_parent(deadline);
        if (available_day <= 0) continue;
        make_union(available_day, available_day-1);
        answer += ramen;
    }
    cout<<answer;
}