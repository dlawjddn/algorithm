/**
 * @file boj_1976.cpp
 * @brief 백준 gold4 여행가자
 * @version 0.1
 * @date 2024-06-28
 * 
 * @copyright Copyright (c) 2024
 * 
 * 자기 자신은 방문이 가능하다는 점.. 이걸 놓쳐서 좀 헤맸다.. 좀 더 꼼꼼히 봐야겠다..
 * 
 */
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int node_cnt = 0, road_cnt = 0;
vector<int> plan;
vector<vector<int> > roads(201);
vector<vector<int> > can_visit(201);

void print_roads() {
    for(int i=1; i<=node_cnt; i++) {
        cout<<"node "<<i<<": ";
        for(int j=0; j<roads[i].size(); j++) {
            cout<<roads[i][j]<<" ";
        }
        cout<<"\n";
    }
}

void print_can_visit() {
    for(int i=1; i<=node_cnt; i++) {
        cout<<"node "<<i<<": ";
        for(int j=0; j<can_visit[i].size(); j++) {
            cout<<can_visit[i][j]<<" ";
        }
        cout<<"\n";
    }
}

void bfs(int spos) {
    vector<bool> visited(201, false);
    queue<int> q;
    q.push(spos);
    visited[spos] = true;
    can_visit[spos].push_back(spos);
    while(!q.empty()) {
        int pos = q.front(); q.pop();
        for(int d=0; d<roads[pos].size(); d++) {
            int npos = roads[pos][d];
            if (visited[npos]) continue;
            q.push(npos);
            visited[npos] = true;
            can_visit[spos].push_back(npos);
        }
    }
}

void ready_for_bfs() {
    for(int i=1; i<=node_cnt; i++) {
        bfs(i);
    }
}

bool check(int start, int dest) {
    for(int visit : can_visit[start]) {
        if (visit == dest) return true;
    }
    return false;
}

int main(){
    cin>>node_cnt>>road_cnt;
    for(int i=1; i<=node_cnt; i++) {
        for(int j=1; j<=node_cnt; j++) {
            int possible; cin>>possible;
            if (possible == 1) {
                roads[i].push_back(j);
                //roads[j].push_back(i);
            }
        }
    }
    for(int i=0; i<road_cnt; i++) {
        int node; cin>>node;
        plan.push_back(node);
    }
    ready_for_bfs();
    //print_can_visit();
    for(int i=1; i<plan.size(); i++) {
        if (!check(plan[i-1], plan[i])) {
            cout<<"NO";
            return 0;
        }
    }
    cout<<"YES";
}