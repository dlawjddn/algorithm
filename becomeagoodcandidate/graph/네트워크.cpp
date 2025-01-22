#include <string>
#include <vector>

using namespace std;

vector<bool> visited;

void dfs(vector<vector<int> >& computers, int node) {
    visited[node] = true;
    for(int x=0; x<computers[node].size(); x++) {
        if (computers[node][x] == 0 || visited[x] || x == node) continue;
        dfs(computers, x);
    }
}

int solution(int n, vector<vector<int>> computers) {
    int answer = 0;
    visited.resize(n, false);
    for(int i=0; i<n; i++) {
        if(visited[i]) continue;
        answer++;
        dfs(computers, i);
    }
    return answer;
}