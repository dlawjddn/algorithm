#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int node_cnt, edge_cnt;
vector<vector<int> > maps;
vector<vector<int> > reverse_maps;
vector<int> indegree;
vector<int> answer;

void print_answer() {
    for(int i=1; i<=node_cnt; i++) cout<<answer[i]<<" ";
    cout<<"\n";
}

int topology_sort() {
    queue<int> q;
    for(int i=1; i<=node_cnt; i++) {
        if (indegree[i] == 0) {
            q.push(i);
            answer[i] = 1;
        }
    }
    while(!q.empty()) {
        int node = q.front(); q.pop();
        for(int x=0; x<maps[node].size(); x++) {
            int nnode = maps[node][x];
            indegree[nnode]--;
            if (indegree[nnode] == 0) {
                int max_value = 0, max_cnt = 0;
                for(int y=0; y<reverse_maps[nnode].size(); y++) {
                    int parent = reverse_maps[nnode][y];
                    if (max_value < answer[parent]) {
                        max_value = answer[parent];
                        max_cnt = 1;
                    } else if (max_value == answer[parent]) max_cnt++;
                }
                if (max_cnt == 1) answer[nnode] = max_value;
                else answer[nnode] = max_value + 1;
                q.push(nnode);
            }
        }
    }
    return *max_element(answer.begin(), answer.end());
}

int main() {
    int test_case; cin>>test_case;
    for(int t=0; t<test_case; t++) {
        int test; cin>>test>>node_cnt>>edge_cnt;
        maps = vector<vector<int> >(node_cnt + 1);
        reverse_maps = vector<vector<int> >(node_cnt + 1);
        answer = vector<int>(node_cnt + 1, 1);
        indegree = vector<int>(node_cnt + 1, 0);
        for(int i=0; i<edge_cnt; i++) {
            int node1, node2; cin>>node1>>node2;
            maps[node1].push_back(node2);
            reverse_maps[node2].push_back(node1);
            indegree[node2]++;
        }
        cout<<test<<" "<<topology_sort()<<"\n";
    }
}