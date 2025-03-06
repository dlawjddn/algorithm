#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int subject_cnt = 0, condition_cnt = 0;
vector<int> indegree;
vector<int> answer;
vector<vector<int> > maps;
queue<int> q;

int main() {
    cin>>subject_cnt>>condition_cnt;
    maps.resize(subject_cnt + 1);
    indegree.resize(subject_cnt + 1, 0);
    answer.resize(subject_cnt + 1, 0);
    for(int i=0; i<condition_cnt; i++) {
        int parent, child; cin>>parent>>child;
        indegree[child]++;
        maps[parent].push_back(child);
    }
    // 루트 과목 설정
    for(int i=1; i<=subject_cnt; i++) {
        if (indegree[i] != 0) continue;
        q.push(i);
        answer[i] = 1;
    }
    // 루트로부터 시작하는 자식 노드 순회
    while(!q.empty()) {
        int parent = q.front(); q.pop();
        for(int x=0; x<maps[parent].size(); x++) {
            int child = maps[parent][x];
            indegree[child]--;
            if (indegree[child] == 0) {
                q.push(child);
                answer[child] = answer[parent] + 1;
            }
        }
    }
    for(int i=1; i<=subject_cnt; i++) cout<<answer[i]<<" ";

}