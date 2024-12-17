#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int student_cnt, order_cnt;
vector<int> parents;

void init() {
    parents.resize(student_cnt + 1);
    for(int i=1; i<=student_cnt; i++) parents[i] = i;
}

int find_parent(int node) {
    if (parents[node] != node) return parents[node] = find_parent(parents[node]);
    return node;
}

void make_union(int node1, int node2) {
    int n1p = find_parent(node1);
    int n2p = find_parent(node2);
    if (n1p < n2p) parents[n2p] = n1p;
    else parents[n1p] = n2p;
}

int main() {
    cin>>student_cnt>>order_cnt;
    init();
    for(int i=0; i<order_cnt; i++) {
        int order_type, team1, team2; cin>>order_type>>team1>>team2;
        if (order_type == 0) {
            make_union(team1, team2);
        } else {
            cout<<((find_parent(team1) == find_parent(team2)) ? "YES\n" : "NO\n");
        }
    }   
}