/**
 * @file 출퇴근길.cpp
 * @brief [HSAT 6회 정기 코딩 인증평가 기출] lv.3 출퇴근길
 * @version 0.1
 * @date 2024-08-26
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int node_cnt = 0, edge_cnt = 0, home = 0, company = 0, answer = 0;
vector<vector<int> > maps;
vector<vector<int> > reverse_maps;
vector<bool> home_company;
vector<bool> company_home;
vector<bool> home_home;
vector<bool> company_company;

void dfs(int pos, vector<bool>& visited, const vector<vector<int> >& graph) {
    visited[pos] = true;
    for(int x = 0; x < graph[pos].size(); x++) {
        int npos = graph[pos][x];
        if (!visited[npos]) {
            dfs(npos, visited, graph);
        }
    }
}

int main(int argc, char** argv){
    cin>>node_cnt>>edge_cnt;
    maps.resize(node_cnt + 1);
    reverse_maps.resize(node_cnt + 1);
    home_company.resize(node_cnt + 1, false);
    company_home.resize(node_cnt + 1, false);
    home_home.resize(node_cnt + 1, false);
    company_company.resize(node_cnt + 1, false);
    for(int i=0; i<edge_cnt; i++) {
        int to, from; cin>>to>>from;
        maps[to].push_back(from);
        reverse_maps[from].push_back(to);
    }
    cin>>home>>company;
    home_company[company] = true;
    company_home[home] = true;
    dfs(home, home_company, maps);
    dfs(company, company_home, maps);
    dfs(home, home_home, reverse_maps);
    dfs(company, company_company, reverse_maps);

    for(int i=1; i<=node_cnt; i++) {
        if (home_company[i] && company_home[i] && home_home[i] && company_company[i]) answer++;
    }
    cout<<answer - 2;
}