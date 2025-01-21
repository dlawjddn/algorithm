#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <algorithm>

using namespace std;

vector<bool> visited;
unordered_map<string, int> cnt;

bool compare(pair<string, int> p1, pair<string, int> p2) {
    if (p1.second == p2.second) return p1.first < p2.first;
    return p1.second > p2.second;
}

void combination(int idx, int depth, int limit, string origin, string menu) {
    if (depth == limit) {
        cnt[menu] += 1;
        return ;
    }
    for(int i = idx; i<visited.size(); i++) {
        if (visited[i]) continue;
        visited[i] = true;
        menu.push_back(origin[i]);
        combination(i, depth + 1, limit, origin, menu);
        visited[i] = false;
        menu.pop_back();
    }
}

vector<string> solution(vector<string> orders, vector<int> course) {
    vector<string> answer;
    for(int i=0; i<orders.size(); i++) sort(orders[i].begin(), orders[i].end());
    for(int i=0; i<course.size(); i++) {
        cnt = unordered_map<string, int>();
        for(int j=0; j<orders.size(); j++) {
            if (course[i] > orders[j].size()) continue;
            visited = vector<bool>(orders[j].size(), false);
            combination(0, 0, course[i], orders[j], "");
        }
        // 현재 cnt에는 course[i]의 숫자로 선택할 수 있는 모든 조합과 그 조합의 선택 받은 수를 담고 있음
        vector<pair<string, int> > infos(cnt.begin(), cnt.end());
        sort(infos.begin(), infos.end(), compare);
        for(int i=0; i<infos.size(); i++) {
            if (infos[i].second < 2 || infos[0].second != infos[i].second) break;
            answer.push_back(infos[i].first);
        }
    }
    sort(answer.begin(), answer.end());
    return answer;
}