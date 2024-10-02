#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int node_cnt = 0, edge_cnt = 0, connect_cnt = 0;
vector<int> parents;
vector<int> cnt;
vector<int> connection;
vector<pair<int, int> > edges;
vector<bool> init;

void print_cnt() {
    for(int i=1; i<=node_cnt; i++) {
        cout<<cnt[i]<<" ";
    }cout<<"\n";
}

int find_parent(int node) {
    if (parents[node] == node) return node;
    return parents[node] = find_parent(parents[node]);
}

void make_union(int parent, int child) {
    parent = find_parent(parent);
    child = find_parent(child);
    if (parent != child) {
        if (cnt[parent] < cnt[child]) swap(parent, child);
        parents[child] = parent;
        cnt[parent] += cnt[child];
        cnt[child] = 0;
    }
}

bool is_same_parent(int node1, int node2) {
    return find_parent(node1) == find_parent(node2);
}

int main(){
    long long answer = 0;
    cin>>node_cnt>>edge_cnt>>connect_cnt;
    parents.resize(node_cnt + 1);
    cnt.resize(node_cnt + 1, 1);
    init.resize(edge_cnt, true);
    for(int i=1; i<=node_cnt; i++) parents[i] = i;
    for(int i=0; i<edge_cnt; i++) {
        int node1, node2; cin>>node1>>node2;
        edges.push_back({node1, node2});
    }
    for(int i=0; i<connect_cnt; i++) {
        int idx; cin>>idx;
        connection.push_back(idx-1);
        init[idx-1] = false;
    }
    for(int i=0; i<edges.size(); i++) {
        if (!init[i]) continue;
        make_union(edges[i].first, edges[i].second);
    }
    reverse(connection.begin(), connection.end());
    for(int i=0; i<connection.size(); i++) {
        auto[node1, node2] = edges[connection[i]];
        //print_cnt();
        int n1p = find_parent(node1);
        int n2p = find_parent(node2);
        if (n1p == n2p) continue;
        // 1. 연결되는 노드를 중심으로 망을 구성하는 노드의 개수 파악 및 크기 계산
        answer += (cnt[n1p] * cnt[n2p]);
        //cout<<answer<<"\n";
        // 2. 노드 간 연결 추가
        make_union(n1p, n2p);
    }
    cout<<answer;
}