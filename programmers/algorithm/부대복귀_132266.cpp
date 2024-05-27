#include <string>
#include <vector>
#include <iostream>
#include <queue>

using namespace std;

vector<vector<int> > maps(100001);

void make_map(vector<vector<int> > roads){
    for(int y=0; y<roads.size(); y++){
        int start = roads[y][0];
        int end = roads[y][1];
        maps[start].push_back(end);
        maps[end].push_back(start);
    }
}

int bfs(int size, int spos, int dest){
    vector<int> visited(size + 1, 0);
    queue<int> q;
    q.push(spos);
    visited[spos] = 1;
    while(!q.empty()){
        int pos = q.front(); q.pop();
        if (pos == dest){
            return visited[pos] - 1;
        }
        for(int d=0; d<maps[pos].size(); d++){
            int npos = maps[pos][d];
            if (visited[npos] != 0) continue;
            q.push(npos);
            visited[npos] = visited[pos] + 1;
        }
    }
    return -1;
}

vector<int> solve(int n, vector<int> sources, int dest){
    vector<int> answer;
    for(int i=0; i<sources.size(); i++){
        answer.push_back(bfs(n, sources[i], dest));
    }
    return answer;
}

vector<int> solution(int n, vector<vector<int>> roads, vector<int> sources, int destination) {
    make_map(roads);
    return solve(n, sources, destination);
}