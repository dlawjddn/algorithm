#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int enter_cnt, plane_cnt, answer = 0;
vector<int> parents;

int find_parent(int node) {
    if (node == parents[node]) return node;
    return parents[node] = find_parent(parents[node]);
}

void make_union(int node1, int node2) {
    int n1p = find_parent(node1);
    int n2p = find_parent(node2);
    if (n1p > n2p) swap(n1p, n2p);
    parents[n2p] = n1p;
}

int main() {
    cin>>enter_cnt>>plane_cnt;
    parents.resize(enter_cnt + 1);
    for(int i=0; i<=enter_cnt; i++) parents[i] = i;
    for(int i=0; i<plane_cnt; i++) {
        int enter; cin>>enter;
        int state = find_parent(enter);
        if (state == 0) break;
        else {
            make_union(enter-1, enter);
            answer++;
        }
    }
    cout<<answer;
}