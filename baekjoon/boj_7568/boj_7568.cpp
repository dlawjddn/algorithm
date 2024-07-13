/**
 * @file boj_7568.cpp
 * @brief 백준 silver5 덩치
 * @version 0.1
 * @date 2024-07-13
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;
    
    vector<pair<int, int>> people(n);
    for (int i = 0; i < n; ++i) {
        cin >> people[i].first >> people[i].second;
    }
    
    vector<int> ranks(n, 1); // 모든 사람의 등수를 1로 초기화

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i != j && people[i].first < people[j].first && people[i].second < people[j].second) {
                ranks[i]++;
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        cout << ranks[i] << " ";
    }
    
    return 0;
}
