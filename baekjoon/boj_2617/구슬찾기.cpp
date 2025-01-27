#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int node_cnt, edge_cnt, answer = 0;
vector<vector<int> > heavy;

int main() {
    cin>>node_cnt>>edge_cnt;
    heavy.resize(node_cnt + 1, vector<int>(node_cnt + 1, 0));
    for(int i=0; i<edge_cnt; i++) {
        int node1, node2; cin>>node1>>node2;
        heavy[node1][node2] = 1;
        heavy[node2][node1] = -1;
    }
    for(int i=1; i<=node_cnt; i++) {
        for(int j=1; j<=node_cnt; j++) {
            for(int k=1; k<=node_cnt; k++) {
                if (heavy[j][k] != 0) continue;
                if (heavy[j][i] == heavy[i][k]) heavy[j][k] = heavy[j][i];
            }
        }
    }
    for(int node=1; node<=node_cnt; node++) {
        int heavy_cnt = 0, light_cnt = 0;
        for(int x=1; x<=node_cnt; x++) {
            if (heavy[node][x] == 1) heavy_cnt++;
            else if (heavy[node][x] == -1) light_cnt++;
        }
        int mid = (node_cnt + 1) / 2;
        if (heavy_cnt >= mid || light_cnt >= mid) answer++;
    }
    cout<<answer;
}