/**
 * @file boj_20303.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-07-03
 * 
 * @copyright Copyright (c) 2024
 * 
 * gg
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int children_cnt = 0, relation_cnt = 0, max_children = 0, answer = 0;
struct Group {
    int num, candies;
    bool operator<(Group other) const {
        return candies < other.candies;
    }
};
vector<int> candies;
vector<int> parents;
vector<pair<int, int> > groups;
vector<vector<int> > dp;

void print_groups() {
    for(int i=0; i<groups.size(); i++) {
        cout << "group" << i+1 << ": ";
        cout << groups[i].first << " " << groups[i].second << "\n";
    }
}

void print_dp() {
    for(int y=0; y<dp.size(); y++) {
        for(int x=0; x<dp[y].size(); x++) {
            cout << dp[y][x] << " ";
        }
        cout << "\n";
    }
}

int find_parent(int node) {
    if (node == parents[node]) return node;
    return parents[node] = find_parent(parents[node]);
}

void make_union(int parent, int child) {
    parent = find_parent(parent);
    child = find_parent(child);
    if (parent != child) {
        parents[child] = parent;
    }
}

void setting_parents() {
    for(int i=1; i<parents.size(); i++) parents[i] = i;
}

int main() {
    cin >> children_cnt >> relation_cnt >> max_children;
    candies.resize(children_cnt + 1);
    parents.resize(children_cnt + 1);
    for(int i=1; i<=children_cnt; i++) {
        cin >> candies[i];
    }
    // 유니온 기초 세팅
    setting_parents();

    // 유니온 작업
    for(int i=0; i<relation_cnt; i++) {
        int node1, node2; cin >> node1 >> node2;
        make_union(node1, node2);
    }

    // 분리 집합 합치기
    vector<bool> visited(children_cnt + 1, false);
    for(int i=1; i<=children_cnt; i++) {
        if (visited[i]) continue;
        pair<int, int> group = make_pair(0, 0);
        int leader = find_parent(i);
        for(int j=1; j<=children_cnt; j++) {
            if (find_parent(j) == leader) {
                group.first += 1;
                group.second += candies[j];
                visited[j] = true;
            }
        }
        groups.push_back(group);
    }

    // knapsack 알고리즘을 통한 계산
    dp.resize(groups.size() + 1, vector<int>(max_children, 0));

    for(int y=1; y<=groups.size(); y++) {
        auto[p_cnt, c_cnt] = groups[y-1];
        for(int x=1; x<max_children; x++) {
            if (p_cnt <= x) {
                dp[y][x] = max(dp[y-1][x], dp[y-1][x - p_cnt] + c_cnt);
            }
            else dp[y][x] = dp[y-1][x];
        }
    }
    // print_groups();
    // print_dp();
    cout<<dp[groups.size()][max_children-1];
}
