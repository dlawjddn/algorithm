/**
 * @file 이모티콘할인행사_150368.cpp
 * @brief 프로그래머스 lv.2 2023 카카오 공채 이모티콘 할인행사
 * @version 0.1
 * @date 2024-08-13
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <string>
#include <vector>
#include <iostream>

using namespace std;

int max_cnt = -1, max_price = -1;
vector<int> sales;

void print_sales() {
    for(auto sale : sales) cout<<sale<<" ";
    cout<<"\n";
}

void solve(vector<vector<int>>& users, vector<int>& emoticons) {
    int cnt = 0;
    int sum_prices = 0;
    for(auto user : users) {
        int percents = user[0];
        int prices = user[1];
        int sum_price = 0;
        for(int i=0; i<emoticons.size(); i++) {
            // 특정 할인율 이상인 이모티콘은 할인된 가격으로 구매
            if (sales[i] >= percents) sum_price += (emoticons[i] * (100 - sales[i]) / 100);
        }
        // 총합 금액이 본인 기준 이상인 경우 -> 임티플 구매
        if (sum_price >= prices)
            cnt++;
        else sum_prices += sum_price;
    }
    if (max_cnt < cnt) {
        max_cnt = cnt;
        max_price = sum_prices;
    } else if (max_cnt == cnt) max_price = max(max_price, sum_prices);
}

void decide_promotion(vector<vector<int>>& users, vector<int>& emoticons, int cnt, int total_cnt) {
    if (cnt == total_cnt){
        solve(users, emoticons);
        return ;
    }
    for(int i=10; i<=40; i+=10) {
        sales[cnt] = i;
        decide_promotion(users, emoticons, cnt + 1, total_cnt);
        sales[cnt] = 0;
    }
}

vector<int> solution(vector<vector<int>> users, vector<int> emoticons) {
    sales.resize(emoticons.size(), 0);
    decide_promotion(users, emoticons, 0, emoticons.size());
    return {max_cnt, max_price};
}