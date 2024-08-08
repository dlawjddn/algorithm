/**
 * @file 요격시스템_181188.cpp
 * @brief 프로그래머스 lv.2 요격시스템
 * @version 0.1
 * @date 2024-08-08
 * 
 * @copyright Copyright (c) 2024
 * 
 * 하.. 씨발..
 * 
 */
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<pair<int, int> > missiles;

int solution(vector<vector<int>> targets) {
    int answer = 0;
    for(auto target : targets) missiles.push_back({target[1], target[0]});
    sort(missiles.begin(), missiles.end());
    
    int compare = -1;
    for(auto missile : missiles) {
        auto[end, start] = missile;
        if (compare <= start) {
            compare = end;
            answer++;
        }
    } 
    return answer;
}

/* 첫번째 오답
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <queue>

using namespace std;
struct Compare {
    bool operator()(pair<int, int> p1, pair<int, int> p2) {
        if (p1.first == p2.first)
            return p1.second > p2.second;
        return p1.first < p2.first;
    }
};
vector<pair<int, int> > missiles;
priority_queue<int> pq;

int solution(vector<vector<int>> targets) {
    int answer = 0;
    for(auto target : targets) {
        missiles.push_back({target[0], target[1]});
    }
    sort(missiles.begin(), missiles.end(), Compare());
    for(auto missile : missiles) {
        if (pq.empty() || missile.first >= pq.top()) {
            pq.push(missile.second);
        }
    }
    return pq.size();
}
*/

/* 두번째 오답
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

vector<pair<int, int> > missiles;

int solution(vector<vector<int>> targets) {
    int answer = 0;
    for(auto target : targets) {
        missiles.push_back({target[0], target[1]});
    }
    sort(missiles.begin(), missiles.end());
    double left = -1.0, right = -1.0;
    for(auto missile : missiles) {
        double mid = (left + right) / 2.0;
        if (left < mid && mid < right) { 
            left = max(left, (double) missile.first);
            right = min(right, (double) missile.second);
        } else { // 포함되지 않는 관계
            left = (double) missile.first;
            right = (double) missile.second;
            answer++;
        }
    }
    return answer;
}
*/