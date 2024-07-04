#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

#define INF 987654321

using namespace std;

int people_cnt = 0, road_cnt = 0, party_place = 0, answer = 0;
vector<vector<pair<int, int> > > maps(1001);
vector<vector<int> > dists;

void print_dist() {
    for(int y=0; y<dists.size(); y++) {
        for(int x=0; x<dists[y].size(); x++) {
            cout<<dists[y][x]<<" ";
        }
        cout<<"\n";
    }
}

void dijkstra(int spos) {
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
    vector<int> visited(people_cnt + 1, INF);
    pq.push(make_pair(0, spos));
    visited[spos] = 0;
    while(!pq.empty()) {
        auto[cost, pos] = pq.top(); pq.pop();
        if (visited[pos] != cost) continue;
        for(int d=0; d<maps[pos].size(); d++) {
            int npos = maps[pos][d].second;
            int ncost = maps[pos][d].first + cost;
            if (visited[npos] <= ncost) continue;
            pq.push(make_pair(ncost, npos));
            visited[npos] = ncost;
        }
    }
    dists[spos] = visited;
}

int main(){
    cin>>people_cnt>>road_cnt>>party_place;
    maps.resize(people_cnt + 1);
    dists.resize(people_cnt + 1, vector<int>(people_cnt + 1, INF));
    for(int i=0; i<road_cnt; i++) {
        int src, dest, cost; cin>>src>>dest>>cost;
        maps[src].push_back(make_pair(cost, dest));
    }
    for(int i=1; i<=people_cnt; i++) {
        dijkstra(i);
    }
    //print_dist();
    for(int i=1; i<=people_cnt; i++) {
        answer = max(answer, dists[i][party_place] + dists[party_place][i]);
    }
    cout<<answer;
}