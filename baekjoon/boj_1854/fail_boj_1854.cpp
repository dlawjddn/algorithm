#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

#define INF 987654321

using namespace std;

int node_cnt, edge_cnt, k;
vector<vector<pair<int, int> > > maps;
vector<vector<pair<int, int> > > reverse_maps;
vector<vector<int> > total_costs;

void print_costs() {
    for(int t=0; t<k; t++) {
        for(int i=1; i<=node_cnt; i++) {
            cout<<total_costs[t][i]<<" ";
        }
        cout<<"\n";
    }
}

vector<int> first_step() {
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
    vector<int> visited(node_cnt + 1, INF);
    pq.push(make_pair(0, 1));
    visited[1] = 0;
    while(!pq.empty()) {
        auto[cost, pos] = pq.top(); pq.pop();
        if (visited[pos] != cost) continue;
        for(int x=0; x<maps[pos].size(); x++) {
            int npos = maps[pos][x].first;
            int ncost = cost + maps[pos][x].second;
            if (visited[npos] <= ncost) continue;
            pq.push(make_pair(ncost, npos));
            visited[npos] = ncost;
        }
    }
    return visited;
}

vector<int> after_step(int step) {
    vector<int> visited = total_costs[step-1];
    for(int dest=1; dest<=node_cnt; dest++) {
        int temp = visited[dest];
        for(int x=0; x<reverse_maps[dest].size(); x++) {
            int mid = reverse_maps[dest][x].first;
            int base_cost = visited[mid];
            int additional_cost = reverse_maps[dest][x].second;
            temp = min(temp, base_cost + additional_cost);
        }
        visited[dest] = ((temp == visited[dest]) ? -1 : temp);
    }
    return visited;
}

int main(){
    cin>>node_cnt>>edge_cnt>>k;
    maps.resize(node_cnt + 1);
    reverse_maps.resize(node_cnt + 1);
    total_costs.resize(k);
    for(int i=0; i<edge_cnt; i++) {
        int start, end, cost; cin>>start>>end>>cost;
        maps[start].push_back(make_pair(end, cost));
        reverse_maps[end].push_back(make_pair(start, cost));
    }
    for(int i=0; i<k; i++) {
        if (i==0) total_costs[0] = first_step();
        else total_costs[i] = after_step(i);
    }
    print_costs();
}