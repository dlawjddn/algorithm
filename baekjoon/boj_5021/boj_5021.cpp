#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <queue>

using namespace std;

int relation_cnt, target_cnt;
unordered_map<string, int> name2idx;
unordered_map<int, string> idx2name;
unordered_map<string, double> scores;
vector<vector<int> > maps;
vector<int> in_degree;
vector<string> targets;
vector<pair<string, pair<string, string> > > inputs;

void print_maps() {
    for(int i=0; i<maps.size(); i++) {
        cout<<idx2name[i]<<": ";
        for(int j=0; j<maps[i].size(); j++) {
            cout<<idx2name[maps[i][j]]<<' ';
        }
        cout<<'\n';
    }
}

void print_indegree() {
    for(int i=0; i<in_degree.size(); i++) {
        cout<<in_degree[i]<<' ';
    }
    cout<<'\n';
}

void input() {
    cin>>relation_cnt>>target_cnt;
    string king; cin>>king;
    name2idx[king] = 0;
    idx2name[0] = king;
    scores[king] = 1.0;

    int last_idx = 1;
    for(int i=0; i<relation_cnt; i++) {
        string child, parent1, parent2; cin>>child>>parent1>>parent2;
        int p1_idx, p2_idx, c_idx;
        if (name2idx.find(parent1) == name2idx.end()) {
            // 처음 나오는 이름인 경우
            p1_idx = last_idx;
            name2idx[parent1] = last_idx;
            idx2name[last_idx++] = parent1;
            scores[parent1] = 0.0;
        } else p1_idx = name2idx[parent1];

        if (name2idx.find(parent2) == name2idx.end()) {
            // 처음 나오는 이름인 경우
            p1_idx = last_idx;
            name2idx[parent2] = last_idx;
            idx2name[last_idx++] = parent2;
            scores[parent2] = 0.0;
        } else p2_idx = name2idx[parent2];

        if (name2idx.find(child) == name2idx.end()) {
            // 처음 나오는 이름인 경우
            c_idx = last_idx;
            name2idx[child] = last_idx;
            idx2name[last_idx++] = child;
            scores[child] = 0.0;
        } else c_idx = name2idx[child];

        inputs.push_back({child, {parent1, parent2}});
    }

    maps.resize(last_idx);
    in_degree.resize(last_idx, 0);

    for(int i=0; i<inputs.size(); i++) {
        auto[child, parents] = inputs[i];
        auto[parent1, parent2] = parents;

        int c_idx = name2idx[child];
        int p1_idx = name2idx[parent1];
        int p2_idx = name2idx[parent2];

        // 진입차수 더하기
        in_degree[c_idx] += 2;

        // 가족 관계 구성
        maps[p1_idx].push_back(c_idx);
        maps[p2_idx].push_back(c_idx);

    }

    for(int i=0; i<target_cnt; i++) {
        string target; cin>>target;
        targets.push_back(target);
    }
}

void topology_sort() {
    queue<int> q;
    for(int i=0; i<in_degree.size(); i++) {
        if (in_degree[i] == 0) {
            q.push(i);
        }
    }
    while(!q.empty()) {
        int idx = q.front(); q.pop();
        for(int x=0; x<maps[idx].size(); x++) {
            int c_idx = maps[idx][x];
            string child = idx2name[c_idx];
            in_degree[c_idx] -= 1;
            scores[child] += (scores[idx2name[idx]] / 2.0);
            if (in_degree[c_idx] == 0) {
                q.push(c_idx);
            }
        }
    }

    double max_value = 0.0;
    string answer;
    for(int i=0; i<targets.size(); i++) {
        string target = targets[i];
        if (max_value < scores[target]) {
            max_value = scores[target];
            answer = target;
        }
    }
    cout<<answer;
}

int main() {
    input();
    topology_sort();
}