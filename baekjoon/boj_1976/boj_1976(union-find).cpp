#include<iostream>
#include <vector>
#include <algorithm>

using namespace std;

int node_cnt = 0, road_cnt = 0;
vector<int> plan;
vector<int> parents;
vector<vector<int> > roads(201);

int get_parent(int node) {
    if (node == parents[node]) return node;
    return parents[node] = get_parent(parents[node]);
}

void make_relation(int parent, int child) {
    parent = get_parent(parent);
    child = get_parent(child);
    parents[child] = parent;
}

bool is_same_parent(int node1, int node2) {
    node1 = get_parent(node1);
    node2 = get_parent(node2);
    if (node1 == node2) return true;
    return false;
}


int main(){
    cin>>node_cnt>>road_cnt;
    parents.resize(node_cnt+1);
    for(int i=1; i<=node_cnt; i++) {
        for(int j=1; j<=node_cnt; j++) {
            int possible; cin>>possible;
            if (possible == 1) {
                roads[i].push_back(j);
            }
        }
    }
    for(int i=0; i<road_cnt; i++) {
        int node; cin>>node;
        plan.push_back(node);
    }
    // 유니온 파인드 기초 세팅
    for(int i=1; i<=node_cnt; i++) parents[i] = i;
    
    // 유니온 생성
    for(int i=0; i<plan.size(); i++) {
        int start = plan[i];
        for(int j=0; j<roads[start].size(); j++) {
            if (parents[start] != parents[roads[start][j]]) make_relation(start, roads[start][j]);
        }
    }

    for (int i = 1; i < plan.size(); i++) {
        if (!is_same_parent(plan[i-1], plan[i])) {
            cout << "NO";
            return 0;
        }
    }
    cout<<"YES";

}