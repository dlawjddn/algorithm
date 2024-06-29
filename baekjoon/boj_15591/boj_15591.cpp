/**
 * @file boj_15591.cpp
 * @brief 백준 gold5 MooTube (Silver) 
 * @version 0.1
 * @date 2024-06-26
 * 
 * @copyright Copyright (c) 2024
 * 
 * 문제가 어려워보였지만, 사실 아무것도 아닌 문제..
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int video_cnt = 0, usado_cnt = 0;
vector<vector<pair<int, int> > > maps(5001);

void print_maps(){
    for(int v=1; v<=video_cnt; v++) {
        cout<<"video "<<v<<": ";
        for(int i=0; i<maps[v].size(); i++) {
            int node = maps[v][i].first;
            int usado = maps[v][i].second;

            cout<<"{ "<<node<<", "<<usado<<" }";
        }
        cout<<"\n";
    }
}

int bfs(int spos, int k) {
    int answer = 0;
    vector<bool> visited(video_cnt+1, false);
    queue<int> q;
    q.push(spos);
    visited[spos] = true;
    while(!q.empty()) {
        int now = q.front(); q.pop();
        for(int v=0; v<maps[now].size(); v++) {
            int npos = maps[now][v].first;
            int nusado = maps[now][v].second;
            if (visited[npos] || nusado < k) continue;
            q.push(npos);
            visited[npos] = true;
            answer++;
        }
    }
    return answer;
}

int main(){
    cin>>video_cnt>>usado_cnt;
    for(int i=1; i<video_cnt; i++) {
        int src; cin>>src;
        int dest; cin>>dest;
        int usado; cin>>usado;
        maps[src].push_back(make_pair(dest, usado));
        maps[dest].push_back(make_pair(src, usado));
    }
    for(int i=0; i<usado_cnt; i++) {
        int k; cin>>k;
        int watching; cin>>watching;
        cout<<bfs(watching, k)<<"\n";
    }

    //print_maps();
}