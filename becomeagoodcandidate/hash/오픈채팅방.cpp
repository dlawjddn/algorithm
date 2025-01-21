#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <unordered_map>

using namespace std;

unordered_map<string, string> nickname;

vector<string> split(string origin) {
    vector<string> result;
    string token;
    istringstream token_stream(origin);
    while(getline(token_stream, token, ' ')) {
        result.push_back(token);
    }
    return result;
}

vector<string> solution(vector<string> record) {
    vector<string> answer;
    vector<pair<string, string> > result;
    
    for(auto r : record) {
        vector<string> splited = split(r);
        if (splited[0] == "Enter") {
            nickname[splited[1]] = splited[2];
            result.push_back({splited[1], splited[0]});
        } else if (splited[0] == "Leave") {
            result.push_back({splited[1], splited[0]});
        } else {
            // 닉네임 변경의 경우
            nickname[splited[1]] = splited[2];
        }
    }
    
    for(int i=0; i<result.size(); i++) {
        string name = nickname[result[i].first];
        if (result[i].second == "Enter") {
            answer.push_back(name + "님이 들어왔습니다.");
        } else {
            answer.push_back(name + "님이 나갔습니다.");
        }
        
    }
    return answer;
}