/**
 * @file 지형이동_62050.cpp
 * @brief 프로그래머스 lv.4 지형이동
 * @version 0.1
 * @date 2024-09-23
 * 
 * @copyright Copyright (c) 2024
 * 
 * 최단거리 문제에 대한 새로운 인사이트를 제공한 문제..
 * 
 * 어느 임의의 점에서 모든 점을 방문해야 한다 -> 내가 DFS 문제로 착각한 이유
 * : 근데 다시 생각해보니, 어느 점에서도 상관없다면 특정한 점에서도 똑같은건데.. 왜 그랬을까
 * 
 * 다익스트라를 그냥 사용하면 누적 합이 안되는데? -> 내가 DFS 문제로 착각한 이유2
 * : 생각해보니, 지금 문제 풀이처럼, 변화된 값만 추가하면 되는 문제긴 하네..
 * 
 * pq.push()에서 answer의 값을 증가시키면 안되는 이유
 * - pq에서 최소 cost를 기준으로 작은 순서대로 꺼내는데, pq에 들어갈 때는 정렬이 되지 않은 상태, 즉 최소 값을 보장하지 못함..
 * - 따라서 pq.push에서 answer의 변동이 생긴다면, 절대 answer의 최소를 보장할 수 없음
 * 
 * 다익스트라에 관한 방문처리 로직의 위치로 이렇게 갈릴 수 있다는게 좀 신기하다. 이런 풀이도 있구나..
 * 처음에 다익스트라로 풀었는데 모두 방문하면서, 누적된 값을 다루는 게 어려워서 틀었는데..
 * 디테일이 부족했던 것 같다
 * 
 */
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>

#define INF 987654321

using namespace std;

int sq_size, answer = 0;
int moveY[4]={0,1,0,-1}, moveX[4]={1,0,-1,0};
vector<vector<bool> > visited;
struct Info {
    int y, x, cost;
    bool operator<(Info other) const {
        return cost > other.cost;
    }
};

Info make_info(int y, int x, int cost) {
    Info info;
    info.y = y;
    info.x = x;
    info.cost = cost;
    return info;
}

bool check_outside(int y, int x) {
    return y < 0 || y >= visited.size() || x < 0 || x >= visited.size();
}

void dijkstra(vector<vector<int>>& land, int height) {
    visited.resize(land.size(), vector<bool>(land.size(), false));
    priority_queue<Info> pq;
    pq.push(make_info(0, 0, 0));
    
    while(!pq.empty()) {
        auto[y, x, cost] = pq.top(); pq.pop();
        if (visited[y][x]) continue;
        visited[y][x] = true;
        answer += cost; // 기본값 + 추가된 값, 기본은 0이니까 계속 추가된 값만 누적해서 계산
        for(int d=0; d<4; d++) {
            int ny = y + moveY[d];
            int nx = x + moveX[d];
            if (check_outside(ny, nx) || visited[ny][nx]) continue;
            int diff = abs(land[ny][nx] - land[y][x]);
            int ncost = (diff > height) ? diff : 0; // 기존 값에서 추가된 값만 추가
            pq.push(make_info(ny, nx, ncost));
            
        }
    }
}

int solution(vector<vector<int>> land, int height) {
    dijkstra(land, height);
    return answer;
}