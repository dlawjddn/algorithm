/**
 * @file K번째수_42748.cpp
 * @brief 프로그래머스 lv.1 K번째 수
 * @version 0.1
 * @date 2024-09-24
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> solution(vector<int> array, vector<vector<int>> commands) {
    vector<int> answer;
    for(auto command : commands) {
        int left = command[0] - 1;
        int right = command[1] - 1;
        int idx = command[2] - 1;
        vector<int> cutted;
        for(int i=left; i<=right; i++) {
            cutted.push_back(array[i]);
        }
        sort(cutted.begin(), cutted.end());
        answer.push_back(cutted[idx]);
    }
    return answer;
}