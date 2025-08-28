#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<bool> visited;
vector<pair<char, int> > chars;
vector<pair<int, char> > answer;

void print_answer() {
    sort(answer.begin(), answer.end());
    for(int i=0; i<answer.size(); i++) {
        cout<<answer[i].second;
    } cout<<'\n';
}

void dfs(int idx) {
    visited[idx] = true;
    answer.push_back({chars[idx].second, chars[idx].first});
    print_answer();
    for(int i=idx; i<chars.size(); i++) {
        if (visited[i] || chars[idx].second >= chars[i].second) continue;
        dfs(i);
    }
}

bool compare(pair<char, int> p1, pair<char, int> p2) {
    if (p1.first == p2.first) return p1.second < p2.second;
    return p1.first < p2.first;
}

int main() {
    string origin; cin>>origin;
    visited.resize(origin.size(), false);
    for(int i=0; i<origin.size(); i++) {
        chars.push_back({origin[i], i});
    }
    sort(chars.begin(), chars.end(), compare);
    for(int i=0; i<chars.size(); i++) {
        if (visited[i]) continue;
        dfs(i);
    }
}