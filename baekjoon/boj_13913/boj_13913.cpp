/**
 * @file other_boj_13913.cpp
 * @brief 백준 gold4 숨바꼭질4
 * @version 0.1
 * @date 2024-07-08
 * 
 * @copyright Copyright (c) 2024
 * 
 * 원트!
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int start, destination, mul[3] = {1, 1, 2}, add[3] = {1, -1, 0};
vector<bool> visited(100001, false);
vector<int> parents(100001, -1);

bool check_outside(int num) {
    return num < 0 || num > 100000;
}

void find_sister() {
    queue<int> q;
    q.push(start);
    visited[start] = true;
    while(!q.empty()) {
        int num = q.front(); q.pop();
        if (num == destination) {
            vector<int> path;
            while(num != -1) {
                path.push_back(num);
                num = parents[num];
            }
            reverse(path.begin(), path.end());
            cout<<path.size() - 1<<"\n";
            for(auto num : path) cout<<num<<" ";
            return ;
        }
        for(int d=0; d<3; d++) {
            int nnum = num * mul[d] + add[d];
            if (check_outside(nnum) || visited[nnum]) continue;
            q.push(nnum);
            visited[nnum] = true;
            parents[nnum] = num;
        }
    }
}

int main(){
    cin>>start>>destination;
    find_sister();
}