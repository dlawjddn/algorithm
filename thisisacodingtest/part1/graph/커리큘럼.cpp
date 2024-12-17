#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int class_cnt;
vector<int> cost_time;
vector<int> add_time;
vector<int> in_degree;
vector<vector<int> > maps;
queue<int> q;

void init() {
    maps.resize(class_cnt + 1);
    add_time.resize(class_cnt + 1, 0);
    cost_time.resize(class_cnt + 1, 0);
    in_degree.resize(class_cnt + 1, 0);
}


int main() {
    cin>>class_cnt;
    init();
    for(int i=1; i<=class_cnt; i++) {
        cin>>cost_time[i];
        int parent;
        while(cin>>parent) {
            if (parent == -1) break;
            // maps 추가, in_degree 추가
            in_degree[i]++;
            maps[parent].push_back(i);
        }
    }
    // 1. 진입차수가 0인 노드는 추가하기
    for(int i=1; i<=class_cnt; i++) {
        if(in_degree[i] == 0) q.push(i);
    }
    while(!q.empty()) {
        int node = q.front(); q.pop(); // -> 수업을 마무리한 것
        // 해당 노드를 부모로 갖는 노드에게 소요 시간 추가와 진입 차수를 줄여야함
        for(int d=0; d<maps[node].size(); d++) {
            int nnode = maps[node][d];
            in_degree[nnode] -= 1;
            add_time[nnode] = max(add_time[nnode], add_time[node] + cost_time[node]);
            if (in_degree[nnode] == 0) {
                // 진입차수가 0이면 큐에 삽입
                q.push(nnode);
            }
        }
    }
    for(int i=1; i<=class_cnt; i++) cout<<(cost_time[i] + add_time[i])<<"\n";
}