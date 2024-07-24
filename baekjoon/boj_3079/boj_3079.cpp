/**
 * @file boj_3079.cpp
 * @brief 백준 gold5 입국심사
 * @version 0.1
 * @date 2024-07-24
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>

#define INF 1e20

using namespace std;

long long info_cnt, people_cnt, answer = INF;
vector<int> infos;

int main(){
    cin>>info_cnt>>people_cnt;
    infos.resize(info_cnt);
    for(int i=0; i<info_cnt; i++) cin>>infos[i];
    sort(infos.begin(), infos.end());
    long long left = 1, right = infos.back() * people_cnt;
    while(left <= right) {
        long long mid = (left + right) / 2;
        long long cnt = 0;
        for(auto info : infos) {
            cnt += (mid / (long long)info);
            if (cnt > people_cnt) break;
        }
        if (cnt >= people_cnt) {
            answer = min(answer, mid);
            right = mid - 1;
        } else left = mid + 1;
    }
    cout<<answer;
}