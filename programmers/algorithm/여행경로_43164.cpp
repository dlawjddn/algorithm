#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

vector<bool> visited(10000, false);
string result = "";

void dfs(string start, int cnt, string route, vector<vector<string> > tickets) {
    if (cnt == tickets.size() && result == ""){
        result = route;
        return ;
    }
    for(int i=0; i<tickets.size(); i++) {
        if (visited[i] || tickets[i][0] != start) continue;
        visited[i] = true;
        dfs(tickets[i][1], cnt + 1, route + tickets[i][1], tickets);
        visited[i] = false;
    }
}

vector<string> solution(vector<vector<string>> tickets) {
    vector<string> answer;
    sort(tickets.begin(), tickets.end());
    dfs("ICN", 0, "ICN", tickets);
    for(int i=0; i<result.size(); i+=3) {
        answer.push_back(result.substr(i, 3));
    }
    return answer;
}
/**
 * @file 여행경로_43164.cpp
 * @brief 프로그래머스 lv.3 여행경로
 * @version 0.1
 * @date 2024-08-18
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <string>
#include <vector>

using namespace std;

vector<string> answer;
vector<bool> visited;

void dfs(vector<string> path, vector<vector<string> >& tickets) {
    if (path.size() == tickets.size() + 1) {
        if (answer.size() == 0) {
            answer = path;
            return ;
        }
        answer = min(answer, path);
        return ;
    }
    string pos = path.back();
    for(int i=0; i<tickets.size(); i++) {
        if (visited[i] || pos != tickets[i][0]) continue;
        visited[i] = true;
        path.push_back(tickets[i][1]);
        dfs(path, tickets);
        path.pop_back();
        visited[i] = false;
    }
}

vector<string> solution(vector<vector<string>> tickets) {
    visited.resize(tickets.size(), false);
    vector<string> path = {"ICN"};
    dfs(path, tickets);
    return answer;
}