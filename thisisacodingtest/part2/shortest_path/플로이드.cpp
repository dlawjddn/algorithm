#include <iostream>
#include <vector>
#include <algorithm>

#define INF 987654321

using namespace std;

int node_cnt, edge_cnt;
vector<vector<pair<int, int> > > maps;
vector<vector<int> > visited;

int main() {
    cin>>node_cnt>>edge_cnt;
    maps.resize(node_cnt + 1, vector<pair<int, int> >(node_cnt + 1));
    visited.resize(node_cnt + 1, vector<int>(node_cnt + 1, INF));
    for(int i=1; i<=node_cnt; i++) visited[i][i] = 0;
    for(int i=0; i<edge_cnt; i++) {
        int node1, node2, cost; cin>>node1>>node2>>cost;
        visited[node1][node2] = min(visited[node1][node2], cost);
    }
    for (int k = 1; k <= node_cnt; k++) {
        for (int i = 1; i <= node_cnt; i++) {
            for (int j = 1; j <= node_cnt; j++) {
                visited[i][j] = min(visited[i][j], visited[i][k] + visited[k][j]);
            }
        }
    }
    for(int i=1; i<=node_cnt; i++) {
        for(int j=1; j<=node_cnt; j++) {
            cout<<((visited[i][j] == INF) ? 0 : visited[i][j])<<" ";
            //cout<<visited[i][j]<<" ";
        }
        cout<<"\n";
    }
}