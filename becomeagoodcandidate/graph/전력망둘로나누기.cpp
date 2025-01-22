#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

#define INF 987654321

using namespace std;

vector<vector<int> > connected;
vector<bool> visited;

int dfs(int node, int cnt, int ban1, int ban2) {
    visited[node] = true;
    for(int i=0; i<connected[node].size(); i++) {
        int nnode = connected[node][i];
        if (visited[nnode] || (node == ban1 && nnode == ban2) || (node == ban2 && nnode == ban1)) continue;
        cnt = max(cnt, dfs(nnode, cnt + 1, ban1, ban2));
    }
    return cnt;
}

int solution(int n, vector<vector<int>> wires) {
    int answer = INF;
    connected.resize(n+1);
    visited.resize(n+1, false);
    for(auto wire : wires) {
        int node1 = wire[0];
        int node2 = wire[1];
        connected[node1].push_back(node2);
        connected[node2].push_back(node1);
    }
    for(auto wire : wires) {
        visited = vector<bool>(n+1, false);
        int node1 = wire[0];
        int node2 = wire[1];
        
        int cnt1 = dfs(node1, 1, node1, node2);
        int cnt2 = dfs(node2, 1, node1, node2);
        
        if (cnt1 == 0 || cnt2 == 0) continue;
        
        answer = min(answer, abs(cnt1 - cnt2));       
    }
    
    return answer;
}