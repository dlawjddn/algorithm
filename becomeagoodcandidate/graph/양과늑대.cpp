#include <string>
#include <vector>

using namespace std;

vector<bool> check; // 이미 지나친 곳이라 양 또는 늑대를 얻을 수 없음
vector<vector<int> > maps;
vector<vector<vector<bool> > > visited;
int sheep_cnt = 0, wolf_cnt = 0, answer = 0;

void dfs(int idx, int s_cnt, int w_cnt, vector<int>& info) {
    if (s_cnt <= w_cnt) return ;
    visited[idx][s_cnt][w_cnt] = true;
    answer = max(answer, s_cnt);
    for(int x=0; x<maps[idx].size(); x++) {
        int nidx = maps[idx][x];
        // 기존에 이미 선택한 노드라면 -> 양과 늑대 추가 없이 순회
        if (check[nidx]) {
            if (visited[nidx][s_cnt][w_cnt]) continue;
            dfs(nidx, s_cnt, w_cnt, info);
        }
        // 기존에 선택하지 않은 노드라면 -> 양 또는 늑대 추가
        else {
            check[nidx] = true;
            // 양인 경우
            if (info[nidx] == 0) {
                if (visited[nidx][s_cnt + 1][w_cnt]) continue;
                dfs(nidx, s_cnt + 1, w_cnt, info);
            }
            // 늑대인 경우
            else {
                if (visited[nidx][s_cnt][w_cnt + 1]) continue;
                dfs(nidx, s_cnt, w_cnt + 1, info);
            }
            check[nidx] = false;
        }
    }
    visited[idx][s_cnt][w_cnt] = false;
}

int solution(vector<int> info, vector<vector<int>> edges) {
    for(int i=0; i<info.size(); i++) {
        (info[i] == 0) ? sheep_cnt++ : wolf_cnt++;
    }
    maps.resize(info.size());
    check.resize(info.size(), false);
    visited.resize(info.size(), vector<vector<bool> >(sheep_cnt + 1, vector<bool>(wolf_cnt + 1, false)));
    for(auto edge : edges) {
        maps[edge[0]].push_back(edge[1]);
        maps[edge[1]].push_back(edge[0]);
    }
    check[0] = true;
    dfs(0, 1, 0, info);
    return answer;
}