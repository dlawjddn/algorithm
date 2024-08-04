/**
 * @file boj_16402.cpp
 * @brief 백준 gold2 제국
 * @version 0.1
 * @date 2024-08-04
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <sstream>

using namespace std;

int node_cnt, war_cnt;
vector<int> parents;
vector<string> answer;
map<string, int> str_countries;
map<int, string> int_countries;

int find_parent(int node) {
    if (node == parents[node]) return node;
    return parents[node] = find_parent(parents[node]);
}

void make_union(int winner, int loser) {
    int w_parent = find_parent(winner);
    int l_parent = find_parent(loser);
    parents[l_parent] = w_parent;
}

bool is_same_parent(int node1, int node2) {
    return find_parent(node1) == find_parent(node2);
}

vector<string> split(string origin, char delimeter) {
    vector<string> result;
    string token;
    istringstream tokenStream(origin);
    while(getline(tokenStream, token, delimeter)) result.push_back(token);
    return result;
}

int main(){
    cin>>node_cnt>>war_cnt; cin.ignore();
    parents.resize(node_cnt);
    for(int i=0; i<node_cnt; i++) parents[i] = i;
    for(int i=0; i<node_cnt; i++) {
        string name; getline(cin, name);
        str_countries.insert({name, i});
        int_countries.insert({i, name});
    }
    for(int i=0; i<war_cnt; i++) {
        string result; getline(cin, result);
        vector<string> splited = split(result, ',');
        int node1 = str_countries[splited[0]];
        int node2 = str_countries[splited[1]];
        int win = stoi(splited[2]);
        if (is_same_parent(node1, node2)) { // 종속 관계인 경우
            int winner = node1;
            int loser = node2;
            if (win == 2) swap(winner, loser);
            parents[winner] = winner;
            parents[loser] = winner;
        } else (win == 1) ? make_union(node1, node2) : make_union(node2, node1);
    }
    for(int i=0; i<parents.size(); i++) {
        if (i == find_parent(i)) answer.push_back(int_countries[i]);
    }
    sort(answer.begin(), answer.end());
    cout<<answer.size()<<"\n";
    for(auto str : answer) cout<<str<<"\n";
}