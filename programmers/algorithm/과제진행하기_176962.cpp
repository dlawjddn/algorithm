/**
 * @file 과제진행하기_176962.cpp
 * @brief 프로그래머스 lv.2 과재 진행하기
 * @version 0.1
 * @date 2024-08-12
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <stack>

using namespace std;

struct Info {
    string name;
    int start, cost;
    
    bool operator<(Info other) const {
        return start < other.start;
    }
};
vector<Info> infos;
stack<pair<string , int> > s;

int convert_minutes(string origin) {
    int hour = stoi(origin.substr(0, 2));
    int minute = stoi(origin.substr(3, 2));
    
    return hour * 60 + minute;
}

Info make_info(vector<string> infos) {
    Info info;
    info.name = infos[0];
    info.start = convert_minutes(infos[1]);
    info.cost = stoi(infos[2]);
    return info;
}

vector<string> solution(vector<vector<string>> plans) {
    vector<string> answer;
    for(auto plan : plans) {
        infos.push_back(make_info(plan));
    }
    sort(infos.begin(), infos.end());
    for(int i=0; i<infos.size(); i++) {
        int start_time = infos[i].start;
        int end_time = (i+1<infos.size()) ? infos[i+1].start : 9999999;
        int now_cost = end_time - start_time;
        if (now_cost > infos[i].cost) { // 현재 작업 소요 시간보다 작업 시간이 더 큰 경우
            now_cost -= infos[i].cost;
            infos[i].cost = 0;
            answer.push_back(infos[i].name);
            while(!s.empty() && now_cost > 0) {
                if (now_cost > s.top().second) {
                    answer.push_back(s.top().first);
                    now_cost -= s.top().second;
                    s.pop();
                } else {
                    s.top().second -= now_cost;
                    if (s.top().second == 0) {
                        answer.push_back(s.top().first);
                        s.pop();
                    }
                    break;
                }
            }
        } else {
            infos[i].cost -= now_cost;
            if (infos[i].cost == 0) answer.push_back(infos[i].name);
            else s.push({infos[i].name, infos[i].cost});
        }
    }
    return answer;
}