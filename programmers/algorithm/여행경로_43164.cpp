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