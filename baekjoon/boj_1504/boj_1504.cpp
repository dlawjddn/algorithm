#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

#define INF 200000001

using namespace std;

int node_cnt, road_cnt, check_point1, check_point2;
vector<vector<pair<int, int> > > maps;
vector<vector<int> > visited;

void print_visited() {
    for(int s=0; s<4; s++) {
        for(int pos = 1; pos<=node_cnt; pos++) {
            cout<<visited[s][pos]<<" ";
        }
        cout<<"\n";
    }
}

void dijkstra(int start, int step) {
    priority_queue<pair<int, int> > pq;
    pq.push(make_pair(0, start));
    visited[step][start] = 0;
    while(!pq.empty()) {
        auto[cost, pos] = pq.top(); pq.pop();
        if (visited[step][pos] != cost) continue;
        for(int x=0; x<maps[pos].size(); x++) {
            int ncost = cost + maps[pos][x].first;
            int npos = maps[pos][x].second;
            if (visited[step][npos] <= ncost) continue;
            pq.push(make_pair(ncost, npos));
            visited[step][npos] = ncost;
        }
    }
}

int main(){
    cin>>node_cnt>>road_cnt;
    maps.resize(node_cnt + 1, vector<pair<int, int> >());
    visited.resize(4, vector<int>(node_cnt + 1, INF));
    for(int i=0; i<road_cnt; i++) {
        int node1, node2, cost; cin>>node1>>node2>>cost;
        maps[node1].push_back(make_pair(cost, node2));
        maps[node2].push_back(make_pair(cost, node1));
    }
    cin>>check_point1>>check_point2;

    dijkstra(1, 0);
    dijkstra(check_point1, 1);
    dijkstra(check_point1, 2);
    dijkstra(check_point2, 3);

    int value1 = visited[0][check_point1] + visited[1][check_point2] + visited[3][node_cnt];
    int value2 = visited[0][check_point2] + visited[1][check_point2] + visited[2][node_cnt];

    //print_visited();

    if ((value1 >= INF && value2 >= INF)) cout<<"-1";
    else cout<<min(value1, value2);

}