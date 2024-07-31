/**
 * @file boj_1516.cpp
 * @brief 백준 gold3 게임 개발
 * @version 0.1
 * @date 2024-07-31
 * 
 * @copyright Copyright (c) 2024
 * 
 * 오랜만에 위상정렬 문제라서 조금 헤맸다..
 * 
 * 위상정렬은 진입차수와 queue를 사용하여 순서를 파악하는 알고리즘인데, pop을 하는 경우에 해당 순서가 지정되는 것으로 이해했다.
 * 하지만 이 문제에서는 건설시간의 최대값을 나타내야하기 때문에 pop을 하는 경우에 건설시간을 기록하는 것이 아니라
 * pop은 순서를 의미하고 결과의 경우는 다른 경우를 의미할 수 있다는 점을 잘 파악해야겠다!!
 * 
 * 위상정렬의 다른 응용 방법을 알게 된 문제이다.
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int node_cnt;
vector<vector<int> > maps;
vector<int> parents;
vector<int> costs;
vector<int> build;
queue<pair<int, int> > q;

void print_parents() {
    for(int i=1; i<=node_cnt; i++) cout<<parents[i]<<" ";
    cout<<"\n";
}

void print_answer() {
    for(int i=1; i<=node_cnt; i++) cout<<costs[i]<<"\n";
}

void topology_sort() {
    for(int i=1; i<=node_cnt; i++) {
        if (parents[i] == 0) {
            q.push(make_pair(i, 0));
            costs[i] += build[i];
        }
    }
    while(!q.empty()) {
        auto[pos, cost] = q.front(); q.pop();
        for(int x=0; x<maps[pos].size(); x++) {
            int npos = maps[pos][x];
            int ncost = costs[pos];
            costs[npos] = max(costs[npos], costs[pos] + build[npos]);
            if (--parents[npos] == 0) {
                q.push(make_pair(npos, ncost));
            }
        }
    }
}

int main(){
    cin>>node_cnt;
    maps.resize(node_cnt + 1);
    parents.resize(node_cnt + 1, 0);
    costs.resize(node_cnt + 1, 0);
    build.resize(node_cnt + 1, 0);
    for(int i=1; i<=node_cnt; i++) {
        cin>>build[i];
        while(1) {
            int before; cin>>before;
            if (before == -1) break;
            maps[before].push_back(i);
            parents[i]++;
        }
    }
    topology_sort();
    print_answer();
}