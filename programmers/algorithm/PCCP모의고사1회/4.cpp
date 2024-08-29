/**
 * @file 4.cpp
 * @brief PCCP 모의고사 1회 4번
 * @version 0.1
 * @date 2024-08-29
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>

using namespace std;

struct Info {
    int score, call_time, process_time;
    bool operator<(Info other) const {
        if (score == other.score) {
            return call_time > other.call_time;
        }
        return score > other.score;
    }
};
vector<Info> programs;
priority_queue<Info> pq;

bool compare(Info a, Info b) {
    if (a.call_time == b.call_time) {
        return a.score < b.score;
    }
    return a.call_time < b.call_time;
}

Info make_info(int score, int call_time, int process_time) {
    Info info;
    info.score = score;
    info.call_time = call_time;
    info.process_time = process_time;
    return info;
}

vector<long long> solution(vector<vector<int>> program) {
    vector<long long> answer;
    answer.resize(11, 0);
    for(auto p : program) {
        int score = p[0];
        int call_time = p[1];
        int process_time = p[2];
        programs.push_back(make_info(score, call_time, process_time));
    }
    sort(programs.begin(), programs.end(), compare);
    long long total_time = 0;
    while(1) {
        // 현재 시간보다 실행 요청이 먼저 들어온 프로그램들은 큐에 모두 넣기
        for(int i=0; i<programs.size(); i++) {
            if ((long long)programs[i].call_time <= total_time) {
                pq.push(programs[i]);
                programs.erase(programs.begin() + i);
                i--;
            }
        }
        if (pq.empty()) {
            total_time = (long long)programs[0].call_time;
            continue;
        }
        // 가장 우선순위가 높은 녀석 하나 선택해서 실행
        auto[score, call_time, process_time] = pq.top(); pq.pop();
        long long waiting_time = total_time - (long long)call_time;
        answer[score] += waiting_time;
        total_time += process_time;
        if (pq.empty() && programs.size() == 0) break;
    }
    answer[0] = total_time;
    return answer;
}