/**
 * @file 길찾기게임_42892.cpp
 * @brief 프로그래머스 lv.3 2019 카카오 공채 길 찾기 게임
 * @version 0.1
 * @date 2024-08-22
 * 
 * @copyright Copyright (c) 2024
 * 
 * c++ 연결 리스트 구현 방법을 알게 된 문제
 * 
 */
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Node {
    int idx, y, x;
    bool operator<(Node other) const {
        if (y == other.y) return x < other.x;
        return y > other.y;
    }
};

struct Tree {
    Node* node;
    Tree* left;
    Tree* right;
    
    Tree(Node* n) : node(n), left(nullptr), right(nullptr) {}
};

void add_node(Tree* parent, Node* child) {
    if (child -> x < parent -> node -> x) {
        if (parent -> left == nullptr) parent->left = new Tree(child);
        else add_node(parent->left, child);
    } else {
        if (parent -> right == nullptr) parent->right = new Tree(child);
        else add_node(parent -> right, child);
    }
}

void pre_order(Tree* root, vector<int>& result) {
    if (root == nullptr) return ;
    result.push_back(root -> node -> idx);
    pre_order(root -> left, result);
    pre_order(root -> right, result);
}

void post_order(Tree* root, vector<int>& result) {
    if (root == nullptr) return;
    post_order(root -> left, result);
    post_order(root -> right, result);
    result.push_back(root -> node -> idx);
}

vector<vector<int>> solution(vector<vector<int>> nodeinfo) {
    vector<vector<int>> answer;
    vector<int> pre_result;
    vector<int> post_result;
    vector<Node> nodes;
    
    for(int i=0; i<nodeinfo.size(); i++) {
        nodes.push_back({i+1, nodeinfo[i][1], nodeinfo[i][0]});
    }
    sort(nodes.begin(), nodes.end());
    
    Tree root(&nodes[0]);
    for(int i=1; i<nodes.size(); i++) {
        add_node(&root, &nodes[i]);
    }
    
    pre_order(&root, pre_result);
    post_order(&root, post_result);
    
    answer.push_back(pre_result);
    answer.push_back(post_result);
    
    return answer;
}

/*
오답 -> 빡구현으로 풀었는데.. 빡구현이 다른 빡구현임..
 */
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

#define INF 987654321

using namespace std;

struct Info {
    int idx, y, x, min_dist, parent;
    bool operator<(Info other) const {
        if (y == other.y) return x < other.x;
        return y > other.y;
    }
};

vector<vector<Info> > nodes;
vector<vector<int> > maps;
vector<int> pre_result;
vector<int> post_result;

Info make_info(int idx, int y, int x, int min_dist, int parent) {
    Info info;
    info.idx = idx;
    info.y = y;
    info.x = x;
    info.min_dist = min_dist;
    info.parent = parent;
    return info;
}

void dfs(int pos) {
    pre_result.push_back(pos);
    for(int x=0; x<maps[pos].size(); x++) {
        dfs(maps[pos][x]);
    }
    post_result.push_back(pos);
}

vector<vector<int>> solution(vector<vector<int>> nodeinfo) {
    vector<vector<int>> answer;
    maps.resize(nodeinfo.size() + 1);
    // 상위 노드 내림차순으로 정렬
    vector<Info> sorted_node;
    for(int i=0; i<nodeinfo.size(); i++) {
        vector<int> node = nodeinfo[i];
        sorted_node.push_back(make_info(i+1, node[1], node[0], INF, -1));
    }
    sort(sorted_node.begin(), sorted_node.end());
    
    // 같은 레벨에 있는 노드로 묶기
    int y = sorted_node[0].y; // 시작하는 y
    vector<Info> temp;
    for(auto node : sorted_node) {
        if (node.y == y) {
            temp.push_back(node);
        } else {
            nodes.push_back(temp); // 기존까지 모았던 같은 레벨 저장
            temp.clear(); // temp 초기화
            temp.push_back(node); // 현재 노드 추가
            y = node.y;
        }
    }
    nodes.push_back(temp); //  마지막 레벨 추가
    
    for(int i=1; i<nodes.size(); i++) { // 2번째 높은 애들부터 마지막까지
        for(int k=0; k<nodes[i].size(); k++) { // 각 해당하는 노드들을 하나씩 잡음
            vector<int> child_cnt(nodes[i-1].size(), 0); // 한 노드의 자식은 2개까지 가능하기 때문
            int my_pos = nodes[i][k].x, choose_idx = 0, choose_dist = INF;
            for(int j=0; j<nodes[i-1].size(); j++) { // 자신의 부모 후보가 되는 녀석을 집는다.
                if (child_cnt[j] >= 2) continue;
                int dist = abs(nodes[i-1][j].x - my_pos);
                if (dist < choose_dist) {
                    choose_idx = j;
                    choose_dist = dist;
                }
            }
            // 자식 노드의 부모 노드가 정해진 상황
            child_cnt[choose_idx]++;
            nodes[i][k].min_dist = choose_dist;
            nodes[i][k].parent = nodes[i-1][choose_idx].idx;
            maps[nodes[i-1][choose_idx].idx].push_back(nodes[i][k].idx);
        }
            
    }
    dfs(nodes[0][0].idx);
    answer.push_back(pre_result);
    answer.push_back(post_result);
    // for(int y=1; y<maps.size(); y++) {
    //     cout<<y<<": ";
    //     for(int x=0; x<maps[y].size(); x++) {
    //         cout<<maps[y][x]<<" ";
    //     }
    //     cout<<"\n";
    // }
    // for(int i=0; i<nodes.size(); i++) {
    //     cout<<"==================\n";
    //     for(int j=0; j<nodes[i].size(); j++) {
    //         cout<<"("<<nodes[i][j].idx<<", "<<nodes[i][j].parent<<") ";
    //     }
    //     cout<<"\n";
    // }
    
    return answer;
}