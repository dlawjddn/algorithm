#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
using namespace std;

struct Info {
    int change_cnt;
    vector<int> numbers;
};
int num_cnt, reverse_cnt;
vector<int> numbers;
vector<int> answer;
set<vector<int> > visited;

int bfs() {
    queue<Info> q;
    q.push({0, numbers});
    visited.insert(numbers);
    while(!q.empty()) {
        auto[cnt, nums] = q.front(); q.pop();
        if (answer == nums) {
            return cnt;
        }
        for(int i=0; i<num_cnt - reverse_cnt + 1; i++) {
            vector<int> nnums = nums;
            reverse(nnums.begin() + i, nnums.begin() + i + reverse_cnt);
            if (visited.find(nnums) != visited.end()) continue;
            q.push({cnt +1, nnums});
            visited.insert(nnums);
        }
    }
    return -1;
}

int main() {
    cin>>num_cnt>>reverse_cnt;
    for(int i=0; i<num_cnt; i++) {
        int num; cin>>num;
        numbers.push_back(num);
    }
    answer = numbers;
    sort(answer.begin(), answer.end());
    cout<<bfs();

}