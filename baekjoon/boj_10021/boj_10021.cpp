/**
 * @file boj_10021.cpp
 * @brief 백준 gold3 watering the fields
 * @version 0.1
 * @date 2024-06-26
 * 
 * @copyright Copyright (c) 2024
 * 
 * 크루스칼 알고리즘과 유니온 파인드에 대해서 확실하게 알게 된 문제
 * 
 * MST(Minimum Spanning Tree)?
 * 최소신장트리란 N개의 정점을 최소 비용으로 연결하되, N-1개의 간선을 통해 연결하는 것을 의미한다. 
 * 
 * 크루스칼 MST의 기본 아이디어
 * 
 * 각 정점들을 최소 비용으로 연결하려면? -> 최소 비용을 갖는 간선부터 연결한다. 
 * N개의 정점을 모두 잇는데 필요한 간선은 N-1개 이기 때문에 정말 필요한 간선만 연결한다. -> 사이클이 생기면 안 된다. (한 정점에 대해서 여러 간선이 나갈 수는 있다)
 * 
 * 사이클을 어떻게 판단할까?
 * 
 * 사이클이 생기면 안된다? visited[]를 사용해서 시작점과 도착점에 대해서 방문처리를 진행해야 하나? 아니다. 
 * 바로 유니온 파인드를 사용해서 정점들의 부모가 같은지를 파악하여 사이클을 파악하는 것이 중요하다.
 * 
 * 왜 유니온 파인드를 사용해서 사이클을 판단 해야할까?
 * 
 * 쉽게 설명하면 시작점이 동일한지를 판단하는 것이다. MST는 최소 비용 간선부터 간선들을 선택한다. 결국 시작점이 존재한다는 말이다.
 * 간선을 추가할 때 각 정점에 대해 시작점이 유니온 파인드로 부모로 지정된다. 
 * 즉, 같은 시작점에서 왔는가? 같은 시작점에서 온 두 정점이라면 이미 선택된 정점이고, 이 정점들을 선택하면 사이클이 발생하는 것이다!
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cmath>
#include <numeric>

using namespace std;

struct Point{
    int src, dest, dist;
    bool operator<(Point other) const { 
        return dist > other.dist;
    }
};
int point_cnt = 0, min_cost = 0;
vector<pair<int, int> > points;
vector<int> parents;
priority_queue<Point> pq;

void print_points() {
    for(auto point : points) {
        cout<<point.first<<" "<<point.second<<"\n";
    }
}

Point make_point(int src, int dest, int dist) {
    Point point;
    point.src = src;
    point.dest = dest;
    point.dist = dist;
    return point;
}

int cal_dist(int idx1, int idx2) {
    return pow(points[idx1].first - points[idx2].first, 2) + pow(points[idx1].second - points[idx2].second, 2);
}
int find_parent(int pos) {
    if (pos == parents[pos]) return pos;
    return parents[pos] = find_parent(parents[pos]);
}

void make_union(int parent, int child) {
    parent = find_parent(parent);
    child = find_parent(child);
    parents[child] = parent;
}

bool is_same_parent(int parent, int child) {
    parent = find_parent(parent);
    child = find_parent(child);
    if (parent == child) return true;
    return false;
}

int main(){
    cin>>point_cnt>>min_cost;
    points.resize(point_cnt);
    parents.resize(point_cnt + 1);
    for(int i=0; i<point_cnt; i++) {
        cin>>points[i].first>>points[i].second;
    }

    // 우선순위 큐에 넣기
    for(int i=0; i<points.size() - 1; i++) {
        int src = i;
        for(int j=i+1; j<points.size(); j++) {
            int dest = j;
            int dist = cal_dist(src, dest);
            pq.push(make_point(src, dest, dist));
        }
    }

    // 유니온 파인드 기초 세팅
    for(int i=1; i<=point_cnt; i++) parents[i] = i;

    // 크루스칼 MST 사용하기
    vector<int> answer;
    while(!pq.empty()) {
        Point now = pq.top(); pq.pop();
        if (now.dist < min_cost) continue;
        if (is_same_parent(now.src, now.dest)) continue;
        make_union(now.src, now.dest);
        answer.push_back(now.dist);
        if (answer.size() == point_cnt - 1) {
            cout<<accumulate(answer.begin(), answer.end(), 0);
            return 0;
        }
        
    }
    cout<<-1;

}