#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int node_cnt, edge_cnt, start, dest;
vector<vector<pair<int, int> > > maps;
vector<int> max_weight;

void print_weight() {
    for(int i=1; i<=node_cnt; i++) cout<<max_weight[i]<<" ";
    cout<<"\n";
}

void dijkstra() {
    priority_queue<pair<int, int>, vector<pair<int, int> >, less<pair<int, int> > > pq;
    pq.push(make_pair(0, start));
    while(!pq.empty()) {
        auto[weight, pos] = pq.top(); pq.pop();
        if (max_weight[pos] != weight) continue;
        for(int x=0; x<maps[pos].size(); x++) {
            int npos = maps[pos][x].first;
            int nweight = max(weight, maps[pos][x].second);
            if (max_weight[npos] >= nweight) continue;
            pq.push(make_pair(nweight, npos));
            max_weight[npos] = nweight;
        }
    }
}

int main(){
    cin>>node_cnt>>edge_cnt;
    maps.resize(node_cnt + 1);
    max_weight.resize(node_cnt + 1, 0);
    for(int i=0; i<edge_cnt; i++) {
        int node1, node2, weight; cin>>node1>>node2>>weight;
        maps[node1].push_back(make_pair(node2, weight));
        maps[node2].push_back(make_pair(node1, weight));
    }
    cin>>start>>dest;
    dijkstra();
    print_weight();
}