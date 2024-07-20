/**
 * @file boj_1744.cpp
 * @brief 백준 gold4 수 묶기
 * @version 0.1
 * @date 2024-07-20
 * 
 * @copyright Copyright (c) 2024
 * 
 * 이렇게 귀찮은 문제일 줄이야.. 성심성의껏 풀어야겠다..
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int answer = 0, zero_cnt = 0;
vector<int> positive;
vector<int> negative;

int main() {
    int arr_size; cin >> arr_size;
    for (int i = 0; i < arr_size; i++) {
        int num; cin >> num;
        if (num > 1) positive.push_back(num);
        else if (num == 1) answer += 1;
        else if (num == 0) zero_cnt++;
        else negative.push_back(num);
    }

    sort(positive.begin(), positive.end(), greater<int>());
    sort(negative.begin(), negative.end());

    // 양수 계산
    if (positive.size() % 2 == 1) {
        answer += positive.back();
        positive.pop_back();
    }
    for (int i = 0; i < positive.size(); i += 2) {
        answer += (positive[i] * positive[i + 1]);
    }

    // 음수 계산 + 0 고려
    if (negative.size() % 2 == 1) {
        if (zero_cnt > 0) {
            negative.pop_back();
        } else {
            answer += negative.back();
            negative.pop_back();
        }
    }
    for (int i = 0; i < negative.size(); i += 2) {
        answer += (negative[i] * negative[i + 1]);
    }

    cout << answer;

    return 0;
}
