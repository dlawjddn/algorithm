#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>

using namespace std;

struct Point{
    int pos, cost;
    
    bool operator< (const Point& other) const{
        return cost > other.cost;
    }
};

vector<vector<pair<int, int> > > map(201);
vector<vector<int> > visited(3, vector<int>(201, 987654321));

Point make_point(int pos, int cost){
    Point point;
    point.pos = pos;
    point.cost = cost;
    return point;
}

void dijkstra(int check, int start){
    priority_queue<Point> pq;
    pq.push(make_point(start, 0));
    visited[check][start] = 0;
    while(!pq.empty()){
        Point now = pq.top(); pq.pop();
        if (now.cost != visited[check][now.pos]) continue;
        for(int d=0; d<map[now.pos].size(); d++){
            int npos = map[now.pos][d].first;
            int ncost = map[now.pos][d].second + now.cost;
            if (ncost >= visited[check][npos]) continue;
            pq.push(make_point(npos, ncost));
            visited[check][npos] = ncost;
        }
    }
}

int solution(int n, int s, int a, int b, vector<vector<int>> fares) {
    for(int i=0; i<fares.size(); i++){
        map[fares[i][0]].push_back(make_pair(fares[i][1], fares[i][2]));
        map[fares[i][1]].push_back(make_pair(fares[i][0], fares[i][2]));
    }
    dijkstra(0, s);
    dijkstra(1, a);
    dijkstra(2, b);
    
    int answer = 987654321;
    for (int i = 1; i <= n; i++) {
        if (visited[0][i] != 987654321 && visited[1][i] != 987654321 && visited[2][i] != 987654321) {
            answer = min(answer, visited[0][i] + visited[1][i] + visited[2][i]);
        }
    }

    return answer;
}
/**
 * @file 합승택시요금_72413.cpp
 * @brief 프로그래머스 lv.3 2021 카카오 공채 합승 택시 요금
 * @version 0.1
 * @date 2024-08-22
 * 
 * @copyright Copyright (c) 2024
 * 
 * 흠.. 저번에 풀었던 문제인데.. 아마 정답을 보고 풀었는지 정답을 구하는게 기가 막힌다
 * 다익스트라를 사용하는 건 알았지만 정답을 구하기가 좀 난감했는데 귀신같은 방법이 있었다..
 * 잘 기억해둬야겠다..
 * 
 */
#include <string>
#include <vector>
#include <algorithm>
#include <queue>

#define INF 987654321

using namespace std;

vector<vector<pair<int, int> > > maps;

vector<int> dijkstra(int n, int spos) {
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
    vector<int> visited(n+1, INF);
    pq.push({0, spos});
    visited[spos] = 0;
    while(!pq.empty()) {
        auto[cost, pos] = pq.top(); pq.pop();
        if (visited[pos] != cost) continue;
        for(int x=0; x<maps[pos].size(); x++) {
            int npos = maps[pos][x].first;
            int ncost = cost + maps[pos][x].second;
            if (visited[npos] <= ncost) continue;
            pq.push({ncost, npos});
            visited[npos] = ncost;
        }
    }
    return visited;
}

int solution(int n, int s, int a, int b, vector<vector<int>> fares) {
    int answer = INF;
    maps.resize(n+1);
    for(vector<int> fare : fares) {
        int node1 = fare[0];
        int node2 = fare[1];
        int cost = fare[2];
        maps[node1].push_back({node2, cost});
        maps[node2].push_back({node1, cost});
    }
    vector<int> to_start = dijkstra(n, s);
    vector<int> to_a = dijkstra(n, a);
    vector<int> to_b = dijkstra(n, b);
    
    for(int t=1; t<=n; t++) {
        if (to_start[t] == INF || to_a[t] == INF || to_b[t] == INF) continue;
        answer = min(answer, to_start[t] + to_a[t] + to_b[t]);
    }
    return answer;
}