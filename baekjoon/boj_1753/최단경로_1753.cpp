#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

int node_cnt = 0, line_cnt = 0, start = 0;
vector<vector<pair<int, int > > > map(200001);
vector<int> visited(200001, 987654321);

struct Info{
    int pos, cost;
    
    bool operator<(Info other) const {
        return cost > other.cost;
    }
};

void print_map(int node_cnt){
    for(int i=1; i<=node_cnt; i++){
        cout<<"i: "<<i<<" ";
        for(int j=0; j<map[i].size(); j++) {
            cout<<map[i][j].first<<" "<<map[i][j].second<<"//";
        }
        cout<<"\n";
    }
}

Info make_info(int pos, int cost) {
    Info info;
    info.pos = pos;
    info.cost = cost;
    return info;
}

void dijkstra(int start) {
    priority_queue<Info> pq;
    visited[start] = 0;
    pq.push(make_info(start, 0));
    while(!pq.empty()) {
        Info now = pq.top(); pq.pop();
        if (visited[now.pos] != now.cost) continue;
        for(int d=0; d<map[now.pos].size(); d++) {
            int npos = map[now.pos][d].first;
            int ncost = now.cost + map[now.pos][d].second;
            if (visited[npos] <= ncost) continue;
            visited[npos] = ncost;
            pq.push(make_info(npos, ncost));
        }
    }

}

int main(){
    cin>>node_cnt>>line_cnt>>start;
    for(int i=0; i<line_cnt; i++){
        int src = 0, dest = 0, cost = 0;
        cin>>src>>dest>>cost;
        map[src].push_back(make_pair(dest, cost));
    }
    dijkstra(start);
    for(int i=1; i<=node_cnt; i++){
        if (visited[i] == 987654321)
            cout<<"INF\n";
        else
            cout<<visited[i]<<"\n";
    }

    //print_map(node_cnt);

}