/**
 * @file 순위검색_72412.cpp
 * @brief 프로그래머스 lv.2 순위 검색
 * @version 0.1
 * @date 2024-08-12
 * 
 * @copyright Copyright (c) 2024
 * 
 * 비트마스킹 꼭 알아야겠징..
 */

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <algorithm>

using namespace std;

struct Person {
    string lang, position, career, food;
    int score;
};

// 다차원 맵을 사용하여 사전 생성
unordered_map<string, vector<int>> people_map;

vector<string> split(string origin, char delimeter) {
    vector<string> result;
    string token;
    istringstream token_stream(origin);
    while(getline(token_stream, token, delimeter)) {
        result.push_back(token);
    }
    return result;
}

vector<string> erase_and(vector<string> splited) {
    vector<string> result;
    for(auto str : splited) {
        if (str == "and") continue;
        result.push_back(str);
    }
    return result;
}

void add_to_map(vector<string> keys, int score) {
    string key = keys[0] + keys[1] + keys[2] + keys[3];
    people_map[key].push_back(score);
}

void init(vector<string> info) {
    for (auto person_info : info) {
        vector<string> tokens = split(person_info, ' ');
        int score = stoi(tokens[4]);
        vector<string> keys = {tokens[0], tokens[1], tokens[2], tokens[3]};
        
        // 가능한 모든 조합에 대해 사람 추가
        for (int i = 0; i < (1 << 4); ++i) {
            vector<string> new_keys = keys;
            for (int j = 0; j < 4; ++j) {
                if (i & (1 << j)) new_keys[j] = "-";
            }
            add_to_map(new_keys, score);
        }
    }

    // 점수 배열을 정렬해 두기
    for (auto &entry : people_map) {
        sort(entry.second.begin(), entry.second.end());
    }
}

int count_valid_scores(vector<int> &scores, int min_score) {
    return scores.end() - lower_bound(scores.begin(), scores.end(), min_score);
}

vector<int> solution(vector<string> info, vector<string> query) {
    vector<int> answer;
    init(info);

    for (auto q : query) {
        vector<string> conditions = erase_and(split(q, ' '));
        string key = conditions[0] + conditions[1] + conditions[2] + conditions[3];
        int score = stoi(conditions[4]);

        if (people_map.find(key) != people_map.end()) {
            answer.push_back(count_valid_scores(people_map[key], score));
        } else {
            answer.push_back(0);
        }
    }
    
    return answer;
}

/*
#include <string>
#include <vector>
#include <iostream>
#include <sstream>

using namespace std;

struct Person {
    string lang, position, career, food;
    int score;
};
vector<Person> person_infos;

Person make_person(vector<string> info) {
    Person person;
    person.lang = info[0];
    person.position = info[1];
    person.career = info[2];
    person.food = info[3];
    person.score = stoi(info[4]);
    return person;
}

vector<string> split(string origin, char delimeter) {
    vector<string> result;
    string token;
    istringstream token_stream(origin);
    while(getline(token_stream, token, delimeter)) {
        result.push_back(token);
    }
    return result;
}

vector<string> erase_and(vector<string> splited) {
    vector<string> result;
    for(auto str : splited) {
        if (str == "and") continue;
        result.push_back(str);
    }
    return result;
}

vector<int> init() {
    vector<int> result;
    for(int i=0; i<person_infos.size(); i++) result.push_back(i);
    return result;
}

vector<int> solution(vector<string> info, vector<string> query) {
    vector<int> answer;
    for(auto person_info : info) {
        person_infos.push_back(make_person(split(person_info, ' ')));
    }
    for(auto q : query) {
        vector<int> selected = init();
        vector<string> conditions = erase_and(split(q, ' '));
        string lang = conditions[0];
        string position = conditions[1];
        string career = conditions[2];
        string food = conditions[3];
        int score = stoi(conditions[4]);
        // 1. 언어
        if (lang != "-") { // 제한 조건인 경우에
            for(int i=0; i<selected.size(); i++) {
                if (selected[i] == - 1 || person_infos[selected[i]].lang == lang) continue;
                selected[i] = -1;
            }
        }
        // 2. 직군
        if (position != "-") { // 제한 조건인 경우에
            for(int i=0; i<selected.size(); i++) {
                if (selected[i] == - 1 || person_infos[selected[i]].position == position) continue;
                selected[i] = -1;
            }
        }
        // 3. 경력
        if (career != "-") { // 제한 조건인 경우에
            for(int i=0; i<selected.size(); i++) {
                if (selected[i] == - 1 || person_infos[selected[i]].career == career) continue;
                selected[i] = -1;
            }
        }
        // 4. 소울푸드
        if (food != "-") { // 제한 조건인 경우에
            for(int i=0; i<selected.size(); i++) {
                if (selected[i] == - 1 || person_infos[selected[i]].food == food) continue;
                selected[i] = -1;
            }
        }
        // 5. 코딩테스트 점수
        for(int i=0; i<selected.size(); i++) {
            if (selected[i] == - 1 || person_infos[selected[i]].score >= score) continue;
            selected[i] = -1;
        }
        int cnt = 0;
        for(auto s : selected) {
            if (s == -1) continue;
            cnt ++;
        }
        answer.push_back(cnt);
    }
    return answer;
}
*/