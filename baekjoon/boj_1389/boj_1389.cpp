/**
 * @file boj_1389.cpp
 * @brief 백준 silver1 케빈 베이컨의 6단계 법칙
 * @version 0.1
 * @date 2024-07-09
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>

#define INF 987654321

using namespace std;

int people_cnt, edge_cnt;
vector<vector<int>> relations;

int main() {
    cin >> people_cnt >> edge_cnt;
    relations.resize(people_cnt + 1, vector<int>(people_cnt + 1, INF));
    for (int i = 1; i <= people_cnt; i++) relations[i][i] = 0;
    for (int i = 0; i < edge_cnt; i++) {
        int person1, person2;
        cin >> person1 >> person2;
        relations[person1][person2] = 1;
        relations[person2][person1] = 1;
    }
    for (int k = 1; k <= people_cnt; k++) {
        for (int i = 1; i <= people_cnt; i++) {
            for (int j = 1; j <= people_cnt; j++) {
                relations[i][j] = min(relations[i][j], relations[i][k] + relations[k][j]);
            }
        }
    }
    int answer = 0, answer_cost = INF;
    for (int me = 1; me <= people_cnt; me++) {
        int my_cost = 0;
        for (int other = 1; other <= people_cnt; other++) {
            if (me == other) continue;
            my_cost += relations[me][other];
        }
        if (my_cost < answer_cost) {
            answer = me;
            answer_cost = my_cost;
        }
    }
    cout << answer;
}
