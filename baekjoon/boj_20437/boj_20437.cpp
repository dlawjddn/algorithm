/**
 * @file boj_20437.cpp
 * @brief 백준 gold5 문자열 게임2
 * @version 0.1
 * @date 2024-07-01
 * 
 * @copyright Copyright (c) 2024
 * 
 * 문제의 조건을 제대로 파악하지 못해서.. 틀린 문제..
 * 두번째 조건에서 특정 문자 모두가 시작과 끝을 구성할 수 있는 줄 알았는데, K개의 조건을 만족하는 문자가 시작과 끝을 구성해야 한다..
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int> > alphas;

pair<int, int> solution(int cnt) {
    int min_value = 987654321;
    int max_value = 0;
    for(int i=0; i<alphas.size(); i++) {
        if (alphas[i].size() < cnt) continue;
        for(int j=0; j<alphas[i].size() - cnt + 1; j++) {
            min_value = min(min_value, alphas[i][j + cnt - 1] - alphas[i][j] + 1);
            max_value = max(max_value, alphas[i][j + cnt - 1] - alphas[i][j] + 1);
        }
    }
    return make_pair(min_value, max_value);
}

int main(){
    int test_case = 0; cin>>test_case;
    for(int i=0; i<test_case; i++) {
        string str; cin>>str;
        int cnt; cin>>cnt;
        // alphas 초기화
        alphas = vector<vector<int> >(26);
        for(int j=0; j<str.size(); j++) {
            alphas[str[j] - 'a'].push_back(j);
        }
        pair<int, int> result = solution(cnt);
        if (result.first == 987654321 || result.second == 0) cout<<"-1\n";
        else cout<<result.first<<" "<<result.second<<"\n";
    }
}