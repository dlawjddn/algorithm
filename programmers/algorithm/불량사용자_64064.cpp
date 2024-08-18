/**
 * @file 불량사용자_64064.cpp
 * @brief 프로그래머스 lv.3 2019 카카오 인턴십 불량 사용자
 * @version 0.1
 * @date 2024-08-18
 * 
 * @copyright Copyright (c) 2024
 * 
 * 아.. 이걸 이렇게 생각하다니.. 진짜 아직 멀었다..
 * 
 */
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

set<set<string> >answer;

bool correct_name(string s1, string s2){
    if (s1.size() != s2.size()) return false;
    for(int i=0; i<s1.size(); i++){
        if (s2[i] != '*' && s1[i] != s2[i]) return false;
    }
    return true;
}

int solution(vector<string> user_id, vector<string> banned_id){
    sort(user_id.begin(), user_id.end());
    do {
        set<string> temp_names;
        for(int i=0; i<banned_id.size(); i++){
            if (correct_name(user_id[i], banned_id[i])){
                temp_names.insert(user_id[i]);
            }
        }
        if (temp_names.size() == banned_id.size()){
            answer.insert(temp_names);
        }
    } while(next_permutation(user_id.begin(), user_id.end()));

    return answer.size();
}