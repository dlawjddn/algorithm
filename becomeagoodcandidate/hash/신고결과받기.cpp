#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <sstream>

using namespace std;

unordered_map<string, int> idx_converter;
unordered_map<string, bool> blocked;
unordered_map<string, unordered_set<string> > attack;
unordered_map<string, unordered_set<string> > defense;

vector<string> split(string origin) {
    vector<string> result;
    string token;
    istringstream token_stream(origin);
    while(getline(token_stream, token, ' ')) {
        result.push_back(token);
    }
    return result;
}

vector<int> solution(vector<string> id_list, vector<string> report, int k) {
    vector<int> answer(id_list.size(), 0);
    for(int i=0; i<id_list.size(); i++) {
        idx_converter[id_list[i]] = i;
    }
    // 신고 데이터 분류하기
    for(int i=0; i<report.size(); i++) {
        vector<string> splited = split(report[i]);
        string attacker = splited[0];
        string defenser = splited[1];
        
        attack[attacker].insert(defenser);
        defense[defenser].insert(attacker);
    }
    
    // 정지 확인하기
    for(auto d : defense) {
        if (d.second.size() < k) continue;
        blocked[d.first] = true;
    }
    
    // 결과 메일 전송하기
    for(auto a : attack) {
        int cnt = 0;
        for(auto hater : a.second) {
            if (blocked[hater]) cnt++;
        }
        answer[idx_converter[a.first]] = cnt;
    }
    return answer;
}