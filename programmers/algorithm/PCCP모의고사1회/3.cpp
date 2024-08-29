/**
 * @file 3.cpp
 * @brief PCCP 모의고사 1회 3번
 * @version 0.1
 * @date 2024-08-29
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <string>
#include <vector>

using namespace std;

vector<string> beans = {"RR", "Rr", "Rr", "rr"};

string dfs(long long gen, long long sequnce) {
    if (gen == 1) return "Rr";
    
    long long parent_sequnce = (sequnce + 3) / 4;
    string parent = dfs(gen - 1, parent_sequnce);
    if (parent == "Rr") {
        return beans[(sequnce + 3) % 4];
    }
    return parent;
}

vector<string> solution(vector<vector<int>> queries) {
    vector<string> answer;
    for(auto query : queries) {
        answer.push_back(dfs(query[0], query[1]));
    }
    return answer;
}