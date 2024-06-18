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