/**
 * @file boj_2660.cpp
 * @brief 백준 gold5 회장 뽑기
 * @version 0.1
 * @date 2024-07-27
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

#define INF 987654321

using namespace std;

int people_cnt;
vector<vector<int> > relations;
vector<vector<int> > ranking;

void print_relations() {
    for(int y=1; y<=people_cnt; y++) {
        cout<<"person: "<<y<<": ";
        for(int x=1; x<=people_cnt; x++) {
            cout<<relations[y][x]<<" ";
        }
        cout<<"\n";
    }
}

int main(){
    cin>>people_cnt;
    ranking.resize(people_cnt + 1);
    relations.resize(people_cnt + 1, vector<int>(people_cnt + 1, INF));
    for(int i=1; i<=people_cnt; i++) relations[i][i] = 0;
    while(1) {
        int person1, person2; cin>>person1>>person2;
        if (person1 == -1 && person2 == -1) break;
        relations[person1][person2] = 1;
        relations[person2][person1] = 1;
    }
    for(int i=1; i<=people_cnt; i++) {
        for(int j=1; j<=people_cnt; j++) {
            for(int k=1; k<=people_cnt; k++) {
                relations[j][k] = min(relations[j][k], relations[j][i] + relations[i][k]);
            }
        }
    }
    for(int person = 1; person <= people_cnt; person++) {
        int rank = 0;
        for(int i=1; i<=people_cnt; i++) {
            if (relations[person][i] != INF) {
                rank = max(rank, relations[person][i]);
            }
        }
        ranking[rank].push_back(person);
    }
    for(int i=1; i<=people_cnt; i++) {
        if (ranking[i].empty()) continue;
        cout<<i<<" "<<ranking[i].size()<<"\n";
        sort(ranking[i].begin(), ranking[i].end());
        for(auto person : ranking[i]) cout<<person<<" ";
        break;
    }
}
