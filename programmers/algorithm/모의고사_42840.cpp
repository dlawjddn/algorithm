/**
 * @file 모의고사_42840.cpp
 * @brief 프로그래머스 lv.1 모의고사
 * @version 0.1
 * @date 2024-09-28
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> solution(vector<int> answers) {
    vector<int> answer;
    vector<int> student1 = {1, 2, 3, 4, 5};
    vector<int> student2 = {2, 1, 2, 3, 2, 4, 2, 5};
    vector<int> student3 = {3, 3, 1, 1, 2, 2, 4, 4, 5, 5};
    vector<int> cnt(3, 0);
    for(int i=0; i<answers.size(); i++) {
        if (answers[i] == student1[i % student1.size()]) cnt[0]++;
        if (answers[i] == student2[i % student2.size()]) cnt[1]++;
        if (answers[i] == student3[i % student3.size()]) cnt[2]++;
    }
    int max_score = *max_element(cnt.begin(), cnt.end());
    for(int i=0; i<cnt.size(); i++) {
        if (max_score == cnt[i]) answer.push_back(i+1);
    }
    
    return answer;
}