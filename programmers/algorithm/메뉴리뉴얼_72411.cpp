/**
 * @file 메뉴리뉴얼_72411.cpp
 * @brief 프로그래머스 lv.2 카카오 2021 공채 메뉴 리뉴얼
 * @version 0.1
 * @date 2024-08-07
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <algorithm>

using namespace std;

vector<bool> visited;
unordered_map<string, int> maps;

void combination(int idx, string origin, string str, int goal) {
    if (str.size() == goal) {
        if (maps.find(str) == maps.end()) { // 존재하지 않는 경우
            maps.insert({str, 1});
        } else { // 이미 존재하는 경우
            maps[str] += 1;
        }
    }
    for(int i=idx; i<origin.size(); i++) {
        if (visited[i]) continue;
        visited[i] = true;
        str += origin[i];
        combination(i, origin, str, goal);
        str.pop_back();
        visited[i] = false;
    }
} 

vector<string> solution(vector<string> orders, vector<int> course) {
    vector<string> answer;
    for(auto &order : orders) sort(order.begin(), order.end());
    for(auto c : course) {
        maps = unordered_map<string, int>();
        for(auto order : orders) {
            visited = vector<bool>(order.size(), false);
            combination(0, order, "", c);
        }
        int max_cnt = 2;
        for(auto map : maps) {
            max_cnt = max(max_cnt, map.second);
        }
        for(auto map : maps) {
            if (map.second == max_cnt) answer.push_back(map.first);
        }
    }
    sort(answer.begin(), answer.end());
    return answer;
}
/**
 * @file 메뉴리뉴얼_72411.cpp
 * @brief 프로그래머스 lv.2 2021 카카오 공채 메뉴 리뉴얼
 * @version 0.1
 * @date 2024-09-27
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <algorithm>

using namespace std;

vector<int> favorite_cnt;
vector<bool> visited;
unordered_map<string, int> order_cnt;

void combination(string menus, int limit, int idx, int cnt, string choose) {
    if (cnt == limit) {
        sort(choose.begin(), choose.end());
        order_cnt[choose] += 1;
        favorite_cnt[choose.size()] = max(favorite_cnt[choose.size()], order_cnt[choose]);
        return ;
    }
    for(int i=idx; i<menus.size(); i++) {
        if (visited[i]) continue;
        visited[i] = true;
        combination(menus, limit, i, cnt + 1, choose + menus[i]);
        visited[i] = false;
    }
}

vector<string> solution(vector<string> orders, vector<int> course) {
    vector<string> answer;
    favorite_cnt.resize(11, 0);
    for(auto order : orders) {
        for(auto cnt : course) {
            visited = vector<bool>(order.size(), false);
            combination(order, cnt, 0, 0, "");
        }
    }
    for(int i=0; i<course.size(); i++) {
        int len = favorite_cnt[course[i]];
        for(auto order : order_cnt) {
            if (order.second < 2 || order.second != len || order.first.size() != course[i]) continue;
            answer.push_back(order.first);
        }
    }
    sort(answer.begin(), answer.end());
    return answer;
}