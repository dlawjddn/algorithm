#include <iostream>
#include <vector>
#include <algorithm>

#define INF 987654321

using namespace std;

struct Info {
    bool t;
    int y, x;
};
int node_cnt, telpo;
vector<Info> nodes;
vector<vector<int> > dist;

int main() {
    cin>>node_cnt>>telpo;
    dist.resize(node_cnt, vector<int>(node_cnt, INF));
    for(int i=0; i<node_cnt; i++) {
        bool tel; int y, x; cin>>tel>>y>>x;
        nodes.push_back({tel, y, x});
    }
    for(int i=0; i<node_cnt; i++) {
        for(int j=0; j<node_cnt; j++) {
            if (i == j) continue;
            Info node1 = nodes[i];
            Info node2 = nodes[j];
            dist[i][j] = abs(node1.y - node2.y) + abs(node1.x - node2.x);
            if (node1.t && node2.t) {
                dist[i][j] = min(dist[i][j], telpo);
            }
        }
    }
    for(int i=0; i<node_cnt; i++) {
        for(int j=0; j<node_cnt; j++) {
            for(int k=0; k<node_cnt; k++) {
                if (j == k || j == i || k == i) continue;
                dist[j][k] = min(dist[j][k], dist[j][i] + dist[i][k]);
            }
        }
    }
    int test_case; cin>>test_case;
    for(int t=0; t<test_case; t++) {
        int node1, node2; cin>>node1>>node2;
        cout<<dist[node1-1][node2-1]<<"\n";
    }
}