/**
 * @file 광물캐기_172972.cpp
 * @brief 프로그래머스 lv.2 광물 캐기
 * @version 0.1
 * @date 2024-08-08
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <string>
#include <vector>

using namespace std;

int answer = 987654321;
vector<vector<int> > costs = {
    {1,1,1},
    {5,1,1},
    {25,5,1}
};

int convert_to_num(string mineral) {
    if (mineral == "diamond") return 0;
    else if (mineral == "iron") return 1;
    return 2;
}

void dfs(vector<int>& picks, vector<string>& minerals, int idx, int tired) {
    if ((picks[0] == 0 && picks[1] == 0 && picks[2] == 0) || idx == minerals.size()) {
        answer = min(answer, tired);
        return ;
    }
    for(int i=0; i<3; i++) {
        if (picks[i] == 0) continue;
        picks[i]--;
        int add_tired = 0;
        int nidx = min(idx+5, (int)minerals.size());
        for(int j=idx; j<nidx; j++) {
            add_tired += costs[i][convert_to_num(minerals[j])];
        }
        dfs(picks, minerals, nidx, tired + add_tired);
        picks[i]++;
    }
}

int solution(vector<int> picks, vector<string> minerals) {
    dfs(picks, minerals, 0, 0);
    return answer;
}