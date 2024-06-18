/**
 * @file 양과늑대_92343.cpp
 * @brief 프로그래머스 lv3 양과늑대
 * @version 0.1
 * @date 2024-06-18
 * 
 * @copyright Copyright (c) 2024
 * 
 * 생각은 너무 잘했는데 디테일이 부족했던 문제..
 * check vector를 사용하는 것은 너무 좋았지만
 * visited, check를 dfs에서 돌아오는 과정에 다시 한번 초기화 해야 하는 부분에서 실수가 있었음.. 과연 실수인가..
 * 좀 더 디테일하게 생각하는 것이 중요해보인다.
 */
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> check;
vector<vector<int> > map(17);
vector<vector<vector<bool> > > visited(17, vector<vector<bool> >(17, vector<bool>(17, false)));
int answer = 1;

void dfs(int pos, int sheep, int wolf){
    visited[pos][sheep][wolf] = true;
    
    for(int i=0; i<map[pos].size(); i++){
        int npos = map[pos][i];
        if (check[npos] == 0){ // 양을 만나는 경우
            if (visited[npos][sheep+1][wolf]) continue;
            check[npos] = 2;
            answer = max(answer, sheep+1);
            dfs(npos, sheep+1, wolf);
            check[npos] = 0;
        } else if (check[npos] == 1) { // 늑대를 만나는 경우
            if (sheep <= wolf + 1 || visited[npos][sheep][wolf+1]) continue;
            check[npos] = 2;
            dfs(npos, sheep, wolf+1);
            check[npos] = 1;
        } else { // 경로에 포함되는 경우
            if (visited[npos][sheep][wolf]) continue;
            dfs(npos, sheep, wolf);
        }
    }
    visited[pos][sheep][wolf] = false;
}

int solution(vector<int> info, vector<vector<int>> edges) {
    for(int i=0; i<edges.size(); i++){
        map[edges[i][0]].push_back(edges[i][1]);
        map[edges[i][1]].push_back(edges[i][0]);
    }
    check = info;
    check[0] = 2;
    dfs(0,1,0);
    return answer;
}