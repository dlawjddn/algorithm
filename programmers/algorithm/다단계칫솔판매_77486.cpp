/**
 * @file 다단계칫솔판매_77486.cpp
 * @brief 프로그래머스 lv.3 2021 Dev-Matching 웹 백엔드 개발 다단계 칫솔 판매
 * @version 0.1
 * @date 2024-08-21
 * 
 * @copyright Copyright (c) 2024
 * 
 * 아.. 문제... 하.. 
 * 각 판매 경우마다 값을 구해줘야함 1 -> 2 -> 3 -> 4 의 관계가 있을 때
 * 4가 10개를 10번 팔아서 1000원씩 10번의 매출이 발생했을 때
 * 
 * 처음에 틀린 경우는 4가 총 10000원의 매출을 발생시켰으니, 3은 1000, 2는 100, 1은 10의 퍼미션을 가져가지만
 * 정답의 경우에는 4가 한번당 10000의 매출을 발생시켰으니 3은 100*10, 2는 10*10, 1은 0*10원의 퍼미션을 가져가게 됨
 * 
 * 하.. 진짜 개짜증난다..
 * 
 */
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

unordered_map<string, string> parents;
unordered_map<string, int> money;

void dfs(string person, int profit) {
    if (person == "-" || profit == 0) return;
    int my_profit = profit - profit / 10;
    int other_profit = profit - my_profit;
    money[person] += my_profit;
    dfs(parents[person], other_profit);
}

vector<int> solution(vector<string> enroll, vector<string> referral, vector<string> seller, vector<int> amount) {
    vector<int> answer;
    // 추천인 관계 설정
    for(int i=0; i<enroll.size(); i++) {
        parents[enroll[i]] = referral[i];
    }
    for(int i=0; i<seller.size(); i++) {
        dfs(seller[i], amount[i] * 100);
    }
    for(int i=0; i<enroll.size(); i++) {
        answer.push_back(money[enroll[i]]);
    }
    return answer;
}

/*
오답코드

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

unordered_map<string, vector<string> > map;
unordered_map<string, int> money;
vector<string> start;

int dfs(string person) {
    for(auto next_person : map[person]) {
        money[person] += dfs(next_person);
    }
    int total_money = money[person];
    money[person] = total_money - (total_money / 10);
    return total_money / 10;
}

void solve() {
    for(int i=0; i<start.size(); i++) {
        // dfs 시작
        dfs(start[i]);
    }
}

vector<int> solution(vector<string> enroll, vector<string> referral, vector<string> seller, vector<int> amount) {
    vector<int> answer;
    // 추천인 관계 설정
    for(int i=0; i<enroll.size(); i++) {
        string child = enroll[i];
        string parent = referral[i];
        if (parent == "-") {
            // 최상단 노드부터 시작하기 위해서 따로 저장
            start.push_back(child);
            continue;
        }
        map[parent].push_back(child);
    }
    // 초기 판매 실적 설정
    for(int i=0; i<seller.size(); i++) {
        money[seller[i]] += (amount[i] * 100);
    }
    solve();
    for(int i=0; i<enroll.size(); i++) {
        answer.push_back(money[enroll[i]]);
    }
    return answer;
}
*/