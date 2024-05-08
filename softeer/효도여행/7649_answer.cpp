#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<pair<int, char> > > streets(5005);
vector<vector<int> > dp(5005, vector<int>(5005, 0));
vector<bool> visited(5005, false);
int answer = 0;

void dfs(int line_cnt, int length, int num, string str, string best){
    visited[num] = true;
    for(int x=0; x<=line_cnt; x++){
        if (length == 0 || x == 0)
            dp[length][x] = 0;
        else if (str[length-1] == best[x-1])
            dp[length][x] = dp[length-1][x-1] + 1;
        else
            dp[length][x] = max(dp[length-1][x], dp[length][x-1]);
        answer = max(answer, dp[length][x]);
    }
    for(auto street : streets[num]){
        if (visited[street.first]) continue;
        dfs(line_cnt, length + 1, street.first, str+street.second, best);
    }
}

int main(int argc, char** argv)
{
    int node_cnt = 0, line_cnt=0;
    cin>>node_cnt>>line_cnt;
    string best;
    cin>>best;

    for(int i=0; i<node_cnt-1; i++){
        int node1 = 0, node2 = 0;
        char alpha;
        cin>>node1>>node2>>alpha;
        streets[node1].push_back(make_pair(node2, alpha));
        streets[node2].push_back(make_pair(node1, alpha));
    }
    dfs(line_cnt, 0, 1, "", best);
    cout<<answer;
}