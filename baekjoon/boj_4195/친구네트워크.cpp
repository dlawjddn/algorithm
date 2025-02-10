#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

vector<int> parents;
vector<int> group_cnt;
unordered_map<string, int> converter;

int find_parent(int node) {
    if (node == parents[node]) return node;
    return parents[node] = find_parent(parents[node]);
}

void make_union(int node1, int node2) {
    int n1p = find_parent(node1);
    int n2p = find_parent(node2);
    //if (n1p > n2p) swap(n1p, n2p);
    if (n1p == n2p) return ;
    parents[n2p] = n1p;
    group_cnt[n1p] += group_cnt[n2p];
    group_cnt[n2p] = 0;
}

bool cant_union(int node1, int node2) {
    return find_parent(node1) == find_parent(node2);
}

int main() {
    int test_case; cin>>test_case;
    for(int t=0; t<test_case; t++) {
        int friendship_cnt; cin>>friendship_cnt;
        converter = unordered_map<string, int>();
        vector<pair<int, int> > friendships;
        int people_cnt = 0;
        for(int i=0; i<friendship_cnt; i++) {
            string name1, name2; cin>>name1>>name2;
            int idx1 = 0, idx2 = 0;
            if (converter.find(name1) == converter.end()) {
                converter[name1] = people_cnt++;
                idx1 = converter[name1];
            } else idx1 = converter[name1];

            if (converter.find(name2) == converter.end()) {
                converter[name2] = people_cnt++;
                idx2 = converter[name2];
            } else idx2 = converter[name2];

            friendships.push_back({idx1, idx2});
        }
        group_cnt = vector<int>(people_cnt, 1);
        parents = vector<int>(people_cnt, 0);
        for(int i=0; i<parents.size(); i++) parents[i] = i;

        for(auto[node1, node2] : friendships) {
            make_union(node1, node2);
            cout<<group_cnt[find_parent(node1)]<<"\n";
        }
    }
}