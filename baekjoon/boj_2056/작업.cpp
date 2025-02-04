#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

vector<int> indegree;
vector<int> working_time;
vector<int> waiting_time;
vector<vector<int> > maps;
priority_queue<int, vector<int>, greater<int> > pq;
int node_cnt;

void init() {
    maps.resize(node_cnt + 1);
    indegree.resize(node_cnt + 1, 0);
    working_time.resize(node_cnt + 1, 0);
    waiting_time.resize(node_cnt + 1, 0);
    for(int i=1; i<=node_cnt; i++) parents[i] = i;
}

int main() {
    cin>>node_cnt;
    init();
    for(int i=1; i<=node_cnt; i++) {
        int cost, parent_cnt; cin>>cost>>parent_cnt;
        working_time[i] = cost;
        for(int j=0; j<parent_cnt; j++) {
            int parent; cin>>parent;
            indegree[i]++;
            maps[parent].push_back(i);
        }
    }

    // 루트 노드부터 시작하기
    for(int i=1; i<=node_cnt; i++) {
        if (indegree[i] == 0) {
            for(int j=0; j<maps[i].size(); j++) {
                int child = maps[i][j];
                waiting_time[child] = max(waiting_time[child], working_time[i] + waiting_time[i]);
            }
            pq.push(i);
        }
    }
    while(!pq.empty()) {
        int parent = pq.top(); pq.pop();
        for(int child : maps[parent]) {
            indegree[child]--;
            waiting_time[child] = max(waiting_time[child], waiting_time[parent] + working_time[parent]);
            if (indegree[child] == 0) pq.push(child);
        }
    }
    int answer = 0;
    for(int i=1; i<=node_cnt; i++) {
        answer = max(answer, waiting_time[i] + working_time[i]);
    }
    cout<<answer;
}