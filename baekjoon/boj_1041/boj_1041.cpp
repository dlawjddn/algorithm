/**
 * @file boj_1041.cpp
 * @brief 백준 gold5 주사위
 * @version 0.1
 * @date 2024-07-24
 * 
 * @copyright Copyright (c) 2024
 * 
 * 문제 진짜 너무 더럽다..
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

#define INF 1e18

using namespace std;

int sq_size;
long long choose_3 = INF, choose_2 = INF, choose_1 = INF;
vector<int> dice(6);

void min_choose() {
    // 3개의 면이 접하는 경우의 최소 합 구하기
    vector<vector<int> > three_faces = {
        {0, 1, 2}, {0, 1, 3}, {0, 3, 4}, {0, 2, 4},
        {5, 1, 2}, {5, 1, 3}, {5, 3, 4}, {5, 2, 4}
    };
    for (auto& triple : three_faces) {
        long long sum = dice[triple[0]] + dice[triple[1]] + dice[triple[2]];
        choose_3 = min(choose_3, sum);
    }

    // 2개의 면이 접하는 경우의 최소 합 구하기
    vector<vector<int> > two_faces = {
        {0, 1}, {0, 2}, {0, 3}, {0, 4},
        {1, 2}, {1, 3}, {1, 5}, 
        {2, 4}, {2, 5},
        {3, 4}, {3, 5}, 
        {4, 5}
    };
    for (auto& pair : two_faces) {
        long long sum = dice[pair[0]] + dice[pair[1]];
        choose_2 = min(choose_2, sum);
    }

    // 1개의 면의 최소 값 구하기
    choose_1 = *min_element(dice.begin(), dice.end());
}

int main() {
    cin >> sq_size;
    for (int i = 0; i < 6; i++) cin >> dice[i];

    if (sq_size == 1) {
        int total_sum = accumulate(dice.begin(), dice.end(), 0);
        int max_value = *max_element(dice.begin(), dice.end());
        cout << total_sum - max_value;
        return 0;
    }

    min_choose();

    long long answer = 0;
	answer += (5 * (long long)sq_size*sq_size - 16 * sq_size + 12) * choose_1;
	answer += 4 * choose_3;
	answer += (8 * sq_size - 12) * choose_2;

    cout << answer;

    return 0;
}
