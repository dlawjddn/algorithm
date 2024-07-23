#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

#define INF 987654321

using namespace std;

int node_cnt, edge_cnt, start, dest;
vector<vector<int> > maps;
vector<vector<pair<int, int> > > path;

void print_maps(){
    for(int y=0; y<maps.size(); y++) {
        for(int x=0; x<maps[y].size(); x++) {
            cout<<maps[y][x]<<" ";
        }
        cout<<"\n";
    }
    cout<<"\n";
}

void print_vector(vector<int> path) {
    for(auto p : path) cout<<p<<" ";
    cout<<"\n";
}

void print_path() {
    for(int y=0; y<path.size(); y++) {
        for(int x=0; x<path[y].size(); x++) {
            cout<<"("<<path[y][x].first<<","<<path[y][x].second<<") ";
        }
        cout<<"\n";
    }
    cout<<"\n";
}

void get_shortest(){
    vector<int> visited(node_cnt, INF);
    priority_queue<pair<int, pair<int, int> >, vector<pair<int, pair<int, int> > >, greater<pair<int, pair<int, int> > > > pq;
    pq.push(make_pair(0, make_pair(-1, start)));
    visited[start] = 0;
    while(!pq.empty()) {
        auto[cost, info] = pq.top(); pq.pop();
        auto[bpos, pos] = info;
        if (visited[pos] != cost) continue;
        if (pos == dest) {
            //print_path();
            while(bpos != -1) {
                //cout<<"before: "<<bpos<<" "<<pos<<"\n";
                pair<int, int> temp = path[bpos][pos];
                maps[bpos][pos] = 0;
                pos = bpos;
                bpos = temp.first;
                //cout<<"after"<<bpos<<" "<<pos<<"\n";
            }
            //cout<<"end\n";
            continue;
        }
        for(int x=0; x<maps[pos].size(); x++) {
            if (maps[pos][x] == 0) continue;
            int npos = x;
            int ncost = cost + maps[pos][x];
            if (visited[npos] < ncost) continue;
            pq.push(make_pair(ncost, make_pair(pos, npos)));
            path[pos][npos] = make_pair(bpos, pos);
            visited[npos] = ncost;
        }
    }

}

int get_almost_shortest() {
    vector<int> visited(node_cnt, INF);
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
    pq.push(make_pair(0, start));
    visited[start] = 0;
    while(!pq.empty()) {
        auto[cost, pos] = pq.top(); pq.pop();
        if (visited[pos] != cost) continue;
        for(int x=0; x<maps[pos].size(); x++) {
            if (maps[pos][x] == 0) continue;
            int npos = x;
            int ncost = cost + maps[pos][x];
            if (visited[npos] <= ncost) continue;
            pq.push(make_pair(ncost, npos));
            visited[npos] = ncost;
        }
    }
    return ((visited[dest] == INF) ? -1 : visited[dest]);

}

int main(){
    while(1) {
        cin>>node_cnt>>edge_cnt;
        if (node_cnt == 0 && edge_cnt == 0) break;
        cin>>start>>dest;
        maps = vector<vector<int> >(node_cnt, vector<int>(node_cnt, 0));
        path = vector<vector<pair<int, int> > >(node_cnt, vector<pair<int, int> >(node_cnt, make_pair(-1, -1)));
        for(int i=0; i<edge_cnt; i++) {
            int spos, dpos, cost; cin>>spos>>dpos>>cost;
            maps[spos][dpos] = cost;
        }
        //print_maps();
        get_shortest();
        //print_maps();
        cout<<get_almost_shortest()<<"\n";
    }
}