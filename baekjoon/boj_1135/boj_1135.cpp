#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int people_cnt;
vector<int> costs;
vector<vector<int> > maps;

void print_costs() {
    for(int i=0; i<costs.size(); i++) cout<<costs[i]<<" ";
    cout<<"\n";
}

int dfs(int node) {
    int max_value = 0;
    for(int i=0; i<maps[node].size(); i++) {
        int child = maps[node][i];
        max_value = max(max_value, dfs(child));
    }
    costs[node] = max_value + 1;
    return costs[node];
}

int main(){
    cin >> people_cnt;
    maps.resize(people_cnt);
    costs.resize(people_cnt, 0);

    for(int i=0; i<people_cnt; i++) {
        int parent; 
        cin >> parent;
        if (parent == -1) continue;
        maps[parent].push_back(i);
    }
    dfs(0);
    cout<<*max_element(costs.begin(), costs.end());
}