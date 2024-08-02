/**
 * @file boj_1138.cpp
 * @brief 백준 silver2 한 줄로 서기
 * @version 0.1
 * @date 2024-08-02
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int number_cnt;
vector<pair<int, int> > numbers;
vector<int> result;

int main(){
    cin>>number_cnt;
    result.resize(number_cnt, 0);
    for(int i=1; i<=number_cnt; i++) {
        int info; cin>>info;
        numbers.push_back({i, info});
    }
    for(int i=0; i<numbers.size(); i++) {
        int cnt = 0;
        for(int j=0; j<result.size(); j++) {
            if (result[j] != 0) continue;
            if (cnt == numbers[i].second) {
                result[j] = numbers[i].first;
                break;
            }
            cnt++;
        }
    }
    for(auto r : result) cout<<r<<" ";
}