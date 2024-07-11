/**
 * @file boj_2800.cpp
 * @brief 백준 gold4 괄호 제거
 * @version 0.1
 * @date 2024-07-11
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <set>

using namespace std;

string origin;
stack<int> s;
set<string> result;
vector<pair<int, int> > brakets;
vector<bool> visited;

vector<int> add_vector(vector<int> choose, int idx) {
    choose.push_back(idx);
    return choose;
}

void make_string(vector<int> choose) {
    vector<bool> except(origin.size(), false);
    for(auto idx : choose) {
        except[brakets[idx].first] = true;
        except[brakets[idx].second] = true;
    }
    string str = "";
    for(int i=0; i<origin.size(); i++) {
        if (except[i]) continue;
        str += origin[i];
    }
    result.insert(str);
}

void dfs(int idx, int dest, vector<int> choose) {
    if (choose.size() == dest) {
        make_string(choose);
        return ;
    }
    for(int i=idx; i<brakets.size(); i++) {
        if (visited[i]) continue;
        visited[i] = true;
        dfs(i, dest, add_vector(choose, i));
        visited[i] = false;
    }
}

int main(){
    cin>>origin;
    for(int i=0; i<origin.size(); i++) {
        if (origin[i] == '(') s.push(i);
        else if (origin[i] == ')' && origin[s.top()] == '(') {
            brakets.push_back(make_pair(s.top(), i));
            s.pop();
        }
    }
    for(int i=1; i<=brakets.size(); i++) {
        visited = vector<bool>(brakets.size(), false);
        dfs(0, i, vector<int>());
    }
    for(auto str : result) cout<<str<<"\n";
}