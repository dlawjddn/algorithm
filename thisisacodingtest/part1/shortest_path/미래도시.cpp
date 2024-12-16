#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

#define INF 987654321

using namespace std;

int node_cnt, edge_cnt, company, meeting;
vector<vector<int> > maps;
vector<vector<int> > visited;

int main() {
    cin>>node_cnt>>edge_cnt;
    maps.resize(node_cnt + 1);
    visited.resize(node_cnt + 1, vector<int>(node_cnt + 1, INF));
    for(int i=0; i<edge_cnt; i++) {
        int node1, node2; cin>>node1>>node2;
        maps[node1].push_back(node2);
        maps[node2].push_back(node1);
        visited[node1][node2] = 1;
        visited[node2][node1] = 1;
    }
    cin>>company>>meeting;

    for(int i=1; i<=node_cnt; i++) {
        for(int j=1; j<=node_cnt; j++) {
            for(int k=1; k<=node_cnt; k++) {
                visited[i][j] = min(visited[i][j], visited[i][k] + visited[k][j]);
            }
        }
    }

    if (visited[1][meeting] == INF || visited[meeting][company] == INF) cout<<-1;
    else cout<<visited[1][meeting] + visited[meeting][company];
}