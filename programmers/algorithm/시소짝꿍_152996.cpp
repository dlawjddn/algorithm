#include <string>
#include <vector>

using namespace std;

// 나올 수 있는 조합의 수
// 1:2, 2:3, 3:4, 1:1
long long solution(vector<int> weights) {
    long long answer = 0;
    vector<long long> cnt(1001, 0);
    for(int i=0; i<weights.size(); i++){
        cnt[weights[i]]++;
    }
    for(int i=0; i<weights.size(); i++){
        // 1:2
        long long partner = weights[i] * 2;
        if (partner <= 1000) answer += cnt[partner];
        
        // 2:3
        if (weights[i] % 2 == 0){
            long long partner = weights[i] / 2 * 3;
            if (partner <= 1000) answer += cnt[partner];
        }
        // 3:4
        if (weights[i] % 3 == 0){
            long long partner = weights[i] / 3 * 4;
            if (partner <= 1000) answer += cnt[partner];
        }
    }
    // 1:1
    for(int i=0; i<cnt.size(); i++){
        if (cnt[i] > 1){
            answer += (cnt[i] * (cnt[i] - 1)) / 2;
        }
    }
    return answer;
}
/**
 * @file 시소짝꿍_152996.cpp
 * @brief 프로그래머스 lv.2 시소짝꿍
 * @version 0.1
 * @date 2024-09-05
 * 
 * @copyright Copyright (c) 2024
 * 
 * 절대 쉬운 문제 아니다.. 두번 틀렸다.. 아이디어 배워가자
 * 
 */
#include <string>
#include <vector>

using namespace std;

// 나올 수 있는 조합의 수
// 1:2, 2:3, 3:4, 1:1
long long solution(vector<int> weights) {
    long long answer = 0;
    vector<long long> cnt(1001, 0);
    for(int i=0; i<weights.size(); i++){
        cnt[weights[i]]++;
    }
    for(int i=0; i<weights.size(); i++){
        // 1:2
        long long partner = weights[i] * 2;
        if (partner <= 1000) answer += cnt[partner];
        
        // 2:3
        if (weights[i] % 2 == 0){
            long long partner = weights[i] / 2 * 3;
            if (partner <= 1000) answer += cnt[partner];
        }
        // 3:4
        if (weights[i] % 3 == 0){
            long long partner = weights[i] / 3 * 4;
            if (partner <= 1000) answer += cnt[partner];
        }
    }
    // 1:1
    for(int i=0; i<cnt.size(); i++){
        if (cnt[i] > 1){
            answer += (cnt[i] * (cnt[i] - 1)) / 2;
        }
    }
    return answer;
}