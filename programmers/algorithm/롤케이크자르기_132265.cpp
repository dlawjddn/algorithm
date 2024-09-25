#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

unordered_map<int, int> map;
unordered_map<int, int> front;

void print_map(){
    for(const auto& pair : map) {
        cout << "Key: " << pair.first << ", Value: " << pair.second << endl;
    }
    cout<<map.size();
}

int solution(vector<int> topping) {
    int answer = 0;
    
    for(int num : topping)
        map[num] += 1;
    
    for(int i = 0; i<topping.size(); i++){
        front[topping[i]] += 1;
        map[topping[i]] -= 1;
        if (map[topping[i]] == 0)
            map.erase(topping[i]);
        if (front.size() == map.size())
            answer++;
    }
    return answer;
}

/**
 * @file 롤케이크자르기_132265.cpp
 * @brief 프로그래머스 lv.2 롤케이크 자르기
 * @version 0.1
 * @date 2024-09-25
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <iostream>

using namespace std;

set<int> front_topping;
set<int> back_topping;
vector<int> front_cnt;
vector<int> back_cnt;

int solution(vector<int> topping) {
    int answer = 0;
    // 앞에서부터 토핑 종류 파악하기
    for(int i=0; i<topping.size(); i++) {
        front_topping.insert(topping[i]);
        front_cnt.push_back(front_topping.size());
    }
    // 뒤에서부터 토핑 종류 파악하기
    for(int i=topping.size() - 1; i>=0; i--) {
        back_topping.insert(topping[i]);
        back_cnt.push_back(back_topping.size());
    }
    back_cnt.pop_back();
    reverse(back_cnt.begin(), back_cnt.end());
    for(int i=0; i<back_cnt.size(); i++) {
        if (front_cnt[i] == back_cnt[i]) answer++;
    }
    return answer;
}
