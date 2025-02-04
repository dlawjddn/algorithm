#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <numeric>

using namespace std;

int node_cnt, edge_cnt;
queue<int> q;
vector<int> indegree;
vector<vector<int> > maps;
vector<vector<int> > needs;

int main() {
    cin>>node_cnt>>edge_cnt;
    maps.resize(node_cnt + 1);
    indegree.resize(node_cnt + 1, 0);
    needs.resize(node_cnt + 1, vector<int>(node_cnt + 1, 0));
    for(int i=0; i<edge_cnt; i++) {
        int child, parent, cnt; cin>>child>>parent>>cnt;
        indegree[child]++;
        maps[parent].push_back(child);
        needs[child][parent] = cnt;
    }
    for(int node=1; node<=node_cnt; node++) {
        if (indegree[node] == 0) {
            q.push(node);
            needs[node][node] = 1;
        }
    }
    while(!q.empty()) {
        int parent = q.front(); q.pop();
        for(int child : maps[parent]) {
            indegree[child]--;
            if (indegree[child] == 0) {
                q.push(child);
                vector<int> temp(node_cnt + 1, 0);
                for(int i=1; i<=node_cnt; i++) {
                    int parent = i;
                    int cnt1 = needs[child][i];
                    for(int j=1; j<=node_cnt; j++) {
                        int product = j;
                        int cnt2 = needs[parent][j];
                        temp[product] += (cnt1 * cnt2);
                    }
                }
                if (accumulate(temp.begin(), temp.end(), 0) != 0) needs[child] = temp;
            }
        }
    }
    for(int x=1; x<=node_cnt; x++) {
        if (needs[node_cnt][x] == 0) continue;
        cout<<x<<" "<<needs[node_cnt][x]<<"\n";
    }
}