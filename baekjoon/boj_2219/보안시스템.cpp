#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

#define INF 987654321

using namespace std;

int node_cnt, edge_cnt;
vector<vector<int> > maps;

int main() {
    cin>>node_cnt>>edge_cnt;
    maps.resize(node_cnt + 1, vector<int>(node_cnt + 1, INF));

    for(int i=0; i<edge_cnt; i++) {
        int node1, node2, cost; cin>>node1>>node2>>cost;
        maps[node1][node2] = min(maps[node1][node2], cost);
        maps[node2][node1] = min(maps[node2][node1], cost);
    }

    for(int i=1; i<=node_cnt; i++) {
        for(int j=1; j<=node_cnt; j++) {
            for(int k=1; k<=node_cnt; k++) {
                maps[j][k] = min(maps[j][k], maps[j][i] + maps[i][k]);
            }
        }
    }

    int answer_cost = INF, answer_node = 0;
    for(int node = 1; node <= node_cnt; node++) {
        int temp_cost = 0;
        for(int nnode = 1; nnode <= node_cnt; nnode++) {
            if (node == nnode || maps[node][nnode] == INF) continue;
            temp_cost += maps[node][nnode];
        }
        if (temp_cost < answer_cost) {
            answer_cost = temp_cost;
            answer_node = node;
        }
    }
    cout<<answer_node;
}