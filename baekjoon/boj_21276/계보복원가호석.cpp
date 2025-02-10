#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_map>

using namespace std;

int node_cnt, edge_cnt;
vector<string> people;
vector<int> in_degree;
vector<vector<int> > maps;
vector<vector<int> > answer;
unordered_map<string, int> to_idx;
unordered_map<int, string> to_name;


void print_answer() {
    for(int y=0; y<answer.size(); y++) {
        cout<<to_name[y]<<" "<<answer[y].size()<<" ";
        sort(answer[y].begin(), answer[y].end());
        for(int x=0; x<answer[y].size(); x++) {
            cout<<to_name[answer[y][x]]<<" ";
        }
        cout<<"\n";
    }
}

void init() {
    maps.resize(node_cnt);
    answer.resize(node_cnt);
    in_degree.resize(node_cnt, 0);
}

int main() {
    cin>>node_cnt;
    init();
    for(int i=0; i<node_cnt; i++) {
        string name; cin>>name;
        people.push_back(name);
    }
    sort(people.begin(), people.end());
    for(int i=0; i<people.size(); i++) {
        to_idx[people[i]] = i;
        to_name[i] = people[i];
    }

    cin>>edge_cnt;
    for(int i=0; i<edge_cnt; i++) {
        string child, parent; cin>>child>>parent;
        int child_idx = to_idx[child];
        int parent_idx = to_idx[parent];
        in_degree[child_idx]++;
        maps[parent_idx].push_back(child_idx);
    }

    queue<int> q;
    vector<string> root;
    for(int i=0; i<in_degree.size(); i++) {
        if (in_degree[i] == 0){
            q.push(i);
            root.push_back(to_name[i]);
        }
    }
    cout<<root.size()<<"\n";
    for(int i=0; i<root.size(); i++) cout<<root[i]<<" ";
    cout<<"\n";

    while(!q.empty()) {
        int parent = q.front(); q.pop();
        for(int x=0; x<maps[parent].size(); x++) {
            int child = maps[parent][x];
            in_degree[child]--;
            if (in_degree[child] == 0) {
                q.push(child);
                answer[parent].push_back(child);
            }
        }
    }
    print_answer();

}