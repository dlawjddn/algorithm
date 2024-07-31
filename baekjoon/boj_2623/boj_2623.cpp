/**
 * @file boj_2623.cpp
 * @brief 백준 gold3 음악 프로그램
 * @version 0.1
 * @date 2024-07-31
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <sstream>
#include <string>

using namespace std;

int node_cnt, people_cnt;
vector<vector<int> > maps;
vector<int> parents;

void print_parents() {
    for(int i=1; i<=node_cnt; i++) cout<<parents[i]<<" ";
    cout<<"\n";
}

void print_result(vector<int> result) {
    for(auto node : result) cout<<node<<"\n";
}

void topology_sort() {
    vector<int> result;
    queue<int> q;
    for(int i=1; i<=node_cnt; i++) {
        if (parents[i] == 0) q.push(i);
    }
    while(!q.empty()) {
        int node = q.front(); q.pop();
        result.push_back(node);
        for(int x=0; x<maps[node].size(); x++) {
            int nnode = maps[node][x];
            if (--parents[nnode] == 0) {
                q.push(nnode);
            }
        }
    }
    if (result.size() == node_cnt) print_result(result);
    else cout<<"0";
}

int main(){
    cin>>node_cnt>>people_cnt;
    maps.resize(node_cnt + 1);
    parents.resize(node_cnt + 1, 0);
    for(int i=0; i<people_cnt; i++) {
        int arr_size; cin>>arr_size;
        vector<int> sequence(arr_size);
        for(int j=0; j<arr_size; j++) {
            cin>>sequence[j];
            if (j != 0) {
                maps[sequence[j-1]].push_back(sequence[j]);
                parents[sequence[j]] += 1;
            }
        }
    }
    topology_sort();
}