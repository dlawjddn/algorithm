/**
 * @file 교차로.cpp
 * @brief [HSAT 3회 정기 코딩 인증평가 기출] 교차로
 * @version 0.1
 * @date 2024-09-02
 * 
 * @copyright Copyright (c) 2024
 * 
 * 하.. 왜 이러지 진짜..
 * 
 */
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

#define INF 2000000000

using namespace std;

int car_cnt = 0;
vector<int> result;
vector<pair<int, char>> cars;
queue<pair<int, int>> qa;
queue<pair<int, int>> qb;
queue<pair<int, int>> qc;
queue<pair<int, int>> qd;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    cin >> car_cnt;
    result.resize(car_cnt, -1);
    for (int i = 0; i < car_cnt; i++) {
        int init; char dir; cin >> init >> dir;
        cars.push_back({init, dir});
        if (dir == 'A') qa.push({init, i});
        else if (dir == 'B') qb.push({init, i});
        else if (dir == 'C') qc.push({init, i});
        else qd.push({init, i});
    }

    int start_time = 0;

    while (true) {
        // Find the minimum time from the front of all queues
        int min_time = INF;
        if (!qa.empty()) min_time = min(min_time, qa.front().first);
        if (!qb.empty()) min_time = min(min_time, qb.front().first);
        if (!qc.empty()) min_time = min(min_time, qc.front().first);
        if (!qd.empty()) min_time = min(min_time, qd.front().first);

        if (min_time == INF) break; // All queues are empty

        start_time = max(start_time, min_time);

        bool exist_a = !qa.empty() && qa.front().first <= start_time;
        bool exist_b = !qb.empty() && qb.front().first <= start_time;
        bool exist_c = !qc.empty() && qc.front().first <= start_time;
        bool exist_d = !qd.empty() && qd.front().first <= start_time;

        // Deadlock condition
        if (exist_a && exist_b && exist_c && exist_d) {
            break;
        }

        // Process cars based on their waiting status
        if (exist_a && !exist_d) {
            auto [init, idx] = qa.front(); qa.pop();
            result[idx] = start_time;
        }
        if (exist_b && !exist_a) {
            auto [init, idx] = qb.front(); qb.pop();
            result[idx] = start_time;
        }
        if (exist_c && !exist_b) {
            auto [init, idx] = qc.front(); qc.pop();
            result[idx] = start_time;
        }
        if (exist_d && !exist_c) {
            auto [init, idx] = qd.front(); qd.pop();
            result[idx] = start_time;
        }

        if (qa.empty() && qb.empty() && qc.empty() && qd.empty()) break;

        start_time++;
    }

    for (int i = 0; i < result.size(); i++) {
        cout << result[i] << "\n";
    }

    return 0;
}