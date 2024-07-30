#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

#define INF 987654321

using namespace std;

int node_cnt, edge_cnt, increase_cnt, start, dest, now_cost;
vector<vector<pair<int, int> > > maps;
vector<vector<int> > visited;
vector<int> now_visited;
vector<int> amounts;

void print_visited() {
    for(int i=0; i<=10; i++) {
        cout<<"increase "<<i<<": ";
        for(int j=1; j<=node_cnt; j++) cout<<visited[i][j]<<" ";
        cout<<"\n";
    }
    cout<<"\n";

}

void print_amounts() {
    cout<<"amounts: ";
    for(int i=0; i<=10; i++) cout<<amounts[i]<<" ";
    cout<<"\n";

}

void dijkstra(int add) {
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
    pq.push(make_pair(0, start));
    visited[add][start] = 0;
    while(!pq.empty()) {
        auto[cost, pos] = pq.top(); pq.pop();
        if (visited[add][pos] != cost) continue;
        for(int x=0; x<maps[pos].size(); x++) {
            int npos = maps[pos][x].first;
            int ncost = cost + maps[pos][x].second + add;
            if (visited[add][npos] <= ncost) continue;
            pq.push(make_pair(ncost, npos));
            visited[add][npos] = ncost;
        }
    }
}

int main(){
    cin>>node_cnt>>edge_cnt>>increase_cnt>>start>>dest;
    maps.resize(node_cnt + 1);
    visited.resize(11, vector<int>(node_cnt + 1, INF));
    for(int i=0; i<edge_cnt; i++) {
        int node1, node2, cost; cin>>node1>>node2>>cost;
        maps[node1].push_back(make_pair(node2, cost));
        maps[node2].push_back(make_pair(node1, cost));
    }
    for(int i=0; i<=10; i++) dijkstra(i);
    for(int i=0; i<=10; i++) {
        if(i==0) now_cost = visited[i][dest];
        amounts.push_back(visited[i][dest] - visited[0][dest]);
    }
    //print_visited();
    //print_amounts();
    cout<<now_cost<<"\n";
    for(int i=0; i<increase_cnt; i++) {
        int increase; cin>>increase;
        now_cost += amounts[increase];
        cout<<now_cost<<"\n";
    }
}