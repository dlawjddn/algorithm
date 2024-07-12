#include <iostream>
#include <vector>
#include <algorithm>

#define INF 987654321

using namespace std;

int node_cnt, edge_cnt, question_cnt;
vector<vector<int> > costs;

int main(){
    cin>>node_cnt>>edge_cnt;
    costs.resize(node_cnt + 1, vector<int>(node_cnt + 1, INF));
    for(int i=0; i<edge_cnt; i++) {
        int src, dest, two_way; cin>>src>>dest>>two_way;
        costs[src][dest] = 0;
        costs[dest][src] = (two_way == 1) ? 0 : 1;
    }

    for(int i=1; i<=node_cnt; i++) costs[i][i] = 0;
    for(int i=1; i<=node_cnt; i++) {
        for(int j=1; j<=node_cnt; j++) {
            for(int k=1; k<=node_cnt; k++) {
                costs[j][k] = min(costs[j][k], costs[j][i] + costs[i][k]);
            }
        }
    }

    cin>>question_cnt;
    for(int i=0; i<question_cnt; i++) {
        int start, end; cin>>start>>end;
        cout<<costs[start][end]<<"\n";
    }
}