/**
 * @file 단어퍼즐_12983.cpp
 * @brief 프로그래머스 lv.4 단어 퍼즐
 * @version 0.1
 * @date 2024-10-02
 * 
 * @copyright Copyright (c) 2024
 * 
 * 음.. DP 문제인걸 감을 잡았지만 DP로 어떻게 풀어야할지.. 모르겠어서..
 * 힙큐를 써도 풀린다는 말을 듣자마자 풀이가 떠올랐다..
 * 
 * 처음에는 dfs를 사용해서 풀려고 했지만.. 역시 생각대로 시간초과가 발생했다
 * 내일 책을 보고 제대로 공부해봐야겠다..!
 * 
 */
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <queue>

#define INF 987654321

using namespace std;

int answer = 987654321;
vector<int> visited;
unordered_map<int, vector<string> > check;

void dfs(int cnt, int idx, int limit) {
    if (cnt > answer || idx > limit) return ;
    if (idx == limit) {
        answer = min(answer, cnt);
        return ;
    }
    for(int i=0; i<check[idx].size(); i++) {
        dfs(cnt + 1, idx + check[idx][i].size(), limit);
    }
}

void dijkstra() {
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
    pq.push({0, 0});
    visited[0] = 0;
    while(!pq.empty()) {
        auto[cnt, idx] = pq.top(); pq.pop();
        if (visited[idx] != cnt) continue;
        for(int x=0; x<check[idx].size(); x++) {
            int ncnt = cnt + 1;
            int nidx = idx + check[idx][x].size();
            if (visited[nidx] <= ncnt) continue;
            pq.push({ncnt, nidx});
            visited[nidx] = ncnt;
        }
    }
}

int solution(vector<string> strs, string t){
    visited.resize(t.size() + 1, INF);
    for(int i=0; i<t.size(); i++) {
        for(int j=0; j<strs.size(); j++) {
            if (t[i] != strs[j][0]) continue;
            string small_str = strs[j];
            if (small_str == t.substr(i, small_str.size())) {
                check[i].push_back(small_str);
            }
        }
    }
    dijkstra();
    return (visited.back() == 987654321) ? -1 : visited.back();
}