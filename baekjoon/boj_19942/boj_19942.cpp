/**
 * @file boj_19942.cpp
 * @brief 백준 gold4 다이어트
 * @version 0.1
 * @date 2024-07-15
 * 
 * @copyright Copyright (c) 2024
 * 
 * 사전순으로 앞서는 것을 출력할 때 기존 벡터가 빈 벡터인 경우에 업데이트가 되지 않음... 주의 요망!
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>

#define INF 987654321

using namespace std;

int food_cnt, answer = INF;
vector<bool> visited;
vector<int> standard;
vector<int> result;
vector<vector<int> > foods;

void print_vector(vector<int> choose) {
    for(auto c : choose) cout << c << " ";
    cout << "\n";
}

void solve(int cost, vector<int> choose) {
    vector<int> sum(5, 0);
    bool satisfied = true;
    for(int i = 0; i < choose.size(); i++) {
        for(int j = 0; j < 4; j++) {
            sum[j] += foods[choose[i]][j];
        }
    }
    for(int i = 0; i < 4; i++) {
        if (standard[i] > sum[i]) {
            satisfied = false;
            break;
        }
    }
    if (satisfied) {
        if (answer > cost) {
            answer = cost;
            result = choose;
        } else if (answer == cost) {
            if (result.empty() || result > choose) {
                result = choose;
            }
        }
    }
}

void dfs(int idx, int cnt, int limit, int cost, vector<int> choose) {
    if (cost > answer) return;
    if (cnt == limit) {
        solve(cost, choose);
        return;
    }
    for(int i = idx; i < foods.size(); i++) {
        if (visited[i]) continue;
        visited[i] = true;
        choose.push_back(i);
        dfs(i, cnt + 1, limit, cost + foods[i][4], choose);
        choose.pop_back();
        visited[i] = false;
    }
}

int main() {
    cin >> food_cnt;
    foods.resize(food_cnt);
    visited.resize(food_cnt);
    standard.resize(4);
    for(int i = 0; i < 4; i++) cin >> standard[i];
    for(int i = 0; i < food_cnt; i++) {
        vector<int> infos(5);
        for(int j = 0; j < 5; j++) cin >> infos[j];
        foods[i] = infos;
    }
    for(int i = 1; i <= food_cnt; i++) {
        dfs(0, 0, i, 0, vector<int>());
    }
    if (answer == INF) cout << "-1";
    else {
        cout << answer << "\n";
        for(auto r : result) cout << r + 1 << " ";
    }
}
