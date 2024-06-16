#include <string>
#include <vector>
#include <iostream>

using namespace std;

vector<int> visited(201, 0);

void print_visited(int n){
    for(int i=0; i<n; i++){
        cout<<visited[i]<<" ";
    }
    cout<<"\n";
}

void dfs(vector<vector<int> > computers, int pos, int network){
    visited[pos] = network;
    for(int i=0; i<computers[pos].size(); i++){
        if (pos == i || visited[i] || computers[pos][i] == 0) continue;
        dfs(computers, i, network);
    }
}

int solution(int n, vector<vector<int>> computers) {
    int answer = 0;
    for(int i=0; i<n; i++){
        if (visited[i]) continue;
        ++answer;
        dfs(computers, i, answer);
    }
    //print_visited(n);
    return answer;
}