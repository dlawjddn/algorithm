/**
 * @file 자동차테스트.cpp
 * @brief HSAT 7회 정기 코딩 인증평가 기출 lv.3 자동차 테스트
 * @version 0.1
 * @date 2024-08-26
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

int car_cnt = 0, question_cnt = 0;
vector<int> car_infos;
unordered_map<int, int> car_index;

int main(int argc, char** argv){
    cin>>car_cnt>>question_cnt;
    car_infos.resize(car_cnt, 0);
    for(int i=0; i<car_cnt; i++) {
        cin>>car_infos[i];
    }
    sort(car_infos.begin(), car_infos.end());
    for(int i=0; i<car_cnt; i++) {
        car_index[car_infos[i]] = i;
    }
    for(int i=0; i<question_cnt; i++) {
        int question; cin>>question;
        int idx = car_index[question]; // 해당 연비를 가진 차의 인덱스를 뽑아냄
        int before = idx;
        int after = car_cnt - idx - 1;
        cout<<before * after<<"\n";
        //long long result = (long long)before * (long long)after;
        //cout<<result<<"\n";
    }
}