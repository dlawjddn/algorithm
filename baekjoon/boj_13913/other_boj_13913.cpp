/**
 * @file other_boj_13913.cpp
 * @brief 백준 gold4 숨바꼭질4
 * @version 0.1
 * @date 2024-07-08
 * 
 * @copyright Copyright (c) 2024
 * 
 * 확실히 경로 찾는건 최근에 배웠던 방식을 쓰는게 훨씬 빠르군!
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct Info {
    int pos, cost;
    vector<int> path;
};
int start, destination, mul[3]={1,1,2}, add[3]={1,-1,0};
vector<int> answer;
vector<bool> visited(100001, false);

Info make_info(int pos, int cost, vector<int> path) {
    path.push_back(pos);
    Info info;
    info.pos = pos;
    info.cost = cost;
    info.path = path;
    return info;
}

bool check_outside(int pos) {
    return pos < 0 || pos > 100000;
}

void find_sister() {
    queue<Info> q;
    q.push(make_info(start, 0, vector<int>()));
    visited[start] = true;
    while(!q.empty()) {
        auto[pos, cost, path] = q.front(); q.pop();
        if (pos == destination) {
            answer = path;
            return ;
        }
        for(int d=0; d<3; d++) {
            int npos = pos * mul[d] + add[d];
            int ncost = cost + 1;
            if (check_outside(npos) || visited[npos]) continue;
            q.push(make_info(npos, ncost, path));
            visited[npos] = true;
        }
    }
}

int main() {
    cin>>start>>destination;
    find_sister();
    cout<<answer.size() - 1<<"\n";
    for(auto num : answer) cout<<num<<" ";
}