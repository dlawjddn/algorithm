#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

bool findout = false;
int n_cnt;
vector<int> nums;
vector<bool> visited;
vector<int> answer;
vector<int> temp_answer;

void dfs(int sidx, int idx) {
    visited[idx] = true;
    temp_answer.push_back(idx);

    if (sidx == nums[idx]) {
        // 사이클 발견!
        findout = true;
        return ;
    }
    if (visited[nums[idx]]) return ;
    
    dfs(sidx, nums[idx]);
    if (findout) return ;
}

int main() {
    cin>>n_cnt;
    visited.resize(n_cnt + 1, false);
    nums.push_back(-1); // 1-based 인덱스를 위해 -1 추가
    for(int i=0; i<n_cnt; i++) {
        int num; cin>>num;
        nums.push_back(num);
    }

    // 사이클 찾기
    for(int i=1; i<=n_cnt; i++) {
        findout = false;
        visited = vector<bool>(n_cnt + 1, false);
        temp_answer = vector<int>();
        
        dfs(i, i);
        if (findout) {
            for(int i=0; i<temp_answer.size(); i++) answer.push_back(temp_answer[i]);
        }
    }
    set<int> result(answer.begin(), answer.end());

    cout<<result.size()<<'\n';
    for(auto ans : result) cout<<ans<<'\n';
}