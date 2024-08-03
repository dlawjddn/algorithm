/**
 * @file boj_4386.cpp
 * @brief 백준 gold3 별자리 만들기
 * @version 0.1
 * @date 2024-08-04
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cmath>

using namespace std;

int star_cnt;
vector<int> parents;
vector<pair<double, double> > stars;
priority_queue<pair<double, pair<int, int> >, vector<pair<double, pair<int, int> > >, greater<pair<double, pair<int, int> > > > pq; 

int find_parent(int node) {
    if (node == parents[node]) return node;
    return parents[node] = find_parent(parents[node]);
}

void make_union(int parent, int child) {
    parent = find_parent(parent);
    child = find_parent(child);
    if (parent > child) parents[child] = parent;
    else parents[parent] = child;
}

bool is_same_parent(int node1, int node2) {
    int n1p = find_parent(node1);
    int n2p = find_parent(node2);
    return n1p == n2p;
}

void make_mst() {
    int cnt = 0;
    double answer = 0.0;
    while(cnt < star_cnt - 1) {
        auto[dist, nodes] = pq.top(); pq.pop();
        auto[node1, node2] = nodes;
        if (is_same_parent(node1, node2)) continue;
        make_union(node1, node2);
        cnt++;
        answer += dist;
    }
    cout<<answer;
}

int main(){
    cin>>star_cnt;
    stars.resize(star_cnt);
    parents.resize(star_cnt);
    for(int i=0; i<star_cnt; i++) parents[i] = i;
    for(int i=0; i<star_cnt; i++) cin>>stars[i].first>>stars[i].second;
    for(int i=0; i<stars.size(); i++) {
        for(int j=i+1; j<stars.size(); j++) {
            double dist = sqrt((pow(stars[i].first - stars[j].first, 2) + pow(stars[i].second - stars[j].second, 2)));
            pq.push({dist, {i, j}});
        }
    }
    make_mst();
}