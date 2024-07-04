/**
 * @file best_practice_1238.cpp
 * @brief 백준 gold3 파티
 * @version 0.1
 * @date 2024-07-04
 * 
 * @copyright Copyright (c) 2024
 * 
 * 당연하지만 생각하지 못했던 부분을 알게 된 문제!
 * 
 * 시작점은 최대 1000개, 간선은 최대 10000개 따라서 최대 시간복잡도는 10,000,000으로
 * 1초 안에 실행되기에는 충분해보였다. 하지만 만약에 간선의 개수가 시작점의 개수가 늘어난다면
 * 다익스트라를 활용한 모든 시작점에서의 도착점, 도착점에서의 시작점의 최소 비용을 알 수는 있지만 시간초과가 발생한다.
 * 
 * 이 문제는 여러 시작점에서의 하나의 도착점을 찍고, 하나의 도착점에서 여러 개의 시작점을 가는 문제이다. 양방향이 아닌 단방향으로 그래프가 주어진다.
 * 이 때, 여러 시작점에서 하나의 도착점을 찍는게 아니라 단방향 그래프를 방향을 반대로 하여 역방향 그래프를 만들어, 도착점에서 각 시작점까지의 최소 비용이
 * 각 시작점에서부터 도착점까지의 최소 비용을 나타내는 것이다.
 * 
 * 따라서, 기존 방식은 1000 * 10000의 시간이 발생했지만, 이 방식은 2 * 10000으로 엄청난 시간 차이를 보인다.
 * 
 * 좋은 방법인 것 같다.
 * 
 */
#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>

#define INF 987654321

using namespace std;

int people_cnt, road_cnt, party_place, answer = 0;
vector<vector<vector<pair<int, int> > > > maps;
vector<int> go_visited;
vector<int> back_visited;

void print_visited(){
    for(int i=1; i<=go_visited.size(); i++) {
        cout<<go_visited[i]<<" ";
    } cout<<"\n";
    for(int i=1; i<=go_visited.size(); i++) {
        cout<<back_visited[i]<<" ";
    } 
}

vector<int> dijkstra(int spos, int check) {
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
    vector<int> visited(people_cnt + 1, INF);
    pq.push(make_pair(0, spos));
    visited[spos] = 0;
    while(!pq.empty()) {
        auto[cost, pos] = pq.top(); pq.pop();
        if (visited[pos] != cost) continue;
        for(int d=0; d<maps[check][pos].size(); d++) {
            int ncost = maps[check][pos][d].first + cost;
            int npos = maps[check][pos][d].second;
            if (visited[npos] <= ncost) continue;
            pq.push(make_pair(ncost, npos));
            visited[npos] = ncost;
        }
    }
    return visited;
}

int main(){
    cin>>people_cnt>>road_cnt>>party_place;
    maps.resize(2, vector<vector<pair<int, int> > >(people_cnt + 1));
    go_visited.resize(people_cnt + 1, INF);
    back_visited.resize(people_cnt + 1, INF);

    for(int i=0; i<road_cnt; i++) {
        int src, dest, cost; cin>>src>>dest>>cost;
        maps[0][src].push_back(make_pair(cost, dest));
        maps[1][dest].push_back(make_pair(cost, src));
    }
    go_visited = dijkstra(party_place, 0);
    back_visited = dijkstra(party_place, 1);

    for(int i=1; i<=people_cnt; i++) {
        answer = max(answer, go_visited[i] + back_visited[i]);
    }
    print_visited();
    cout<<"\n";
    cout<<answer;
}