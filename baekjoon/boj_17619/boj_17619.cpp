/**
 * @file boj_17619.cpp
 * @brief 백준 gold3 개구리 점프
 * @version 0.1
 * @date 2024-08-04
 * 
 * @copyright Copyright (c) 2024
 * 
 * 유니온 파인드 문제의 유형 중 하나
 * 
 * 우선순위 큐를 사용하여, 누적된 값에서 비교가 가능한 경우를 파악하는 경우
 * 이러한 경우에 pq를 사용하여 이동이 가능한(연속적으로 선택이 가능한 경우) 경우마다 union을 진행하고
 * 매 값마다 push를 진행하여 비교를 진행하여 최종 parent 어떤 한 노드에 대해서 연결이 가능한 모든 노드에 대해서 업데이트가 된 상황이다. 
 * 
 * 우선순위 큐 + 유나온 파인드 문제를 알아버렸다.. 이해했다!!
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct Compare{
    bool operator()(pair<pair<int, int>, int> p1, pair<pair<int, int>, int> p2) {
        if (p1.first.first == p2.first.first) {
            return p1.first.second > p2.first.second;
        }
        return p1.first.first < p2.first.first;
    }
};

int tree_cnt, question_cnt;
vector<int> parents;
vector<pair<pair<int, int>, int> > trees;
priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;

int find_parent(int node) {
    if (node == parents[node]) return node;
    return parents[node] = find_parent(parents[node]);
}

void make_union(int parent, int child) {
    parent = find_parent(parent);
    child = find_parent(child);
    if (parent < child) parents[child] = parent;
    else parents[parent] = child;
}

bool is_same_parent(int node1, int node2) {
    return find_parent(node1) == find_parent(node2);
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> tree_cnt >> question_cnt;
    parents.resize(tree_cnt + 1);
    for (int i = 1; i <= tree_cnt; i++) parents[i] = i;
    for (int i = 1; i <= tree_cnt; i++) {
        int sx, dx, y; cin >> sx >> dx >> y;
        trees.push_back({{sx, dx}, i});
    }
    sort(trees.begin(), trees.end(), Compare());
    for (auto tree : trees) {
        while (!pq.empty() && tree.first.first > pq.top().first) pq.pop();
        if (!pq.empty() && tree.first.first <= pq.top().first) {
            make_union(tree.second, pq.top().second);
        }
        pq.push({tree.first.second, tree.second});
    }
    for (int i = 0; i < question_cnt; i++) {
        int node1, node2; cin >> node1 >> node2;
        cout << (is_same_parent(node1, node2) ? "1\n" : "0\n");
    }
}
