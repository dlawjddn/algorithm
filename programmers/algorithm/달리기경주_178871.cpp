/**
 * @file 달리기경주_178871.cpp\
 * @brief 프로그래머스 lv.1 달리기 경주
 * @version 0.1
 * @date 2024-09-05
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

unordered_map<string, int> ranks;

vector<string> solution(vector<string> players, vector<string> callings) {
    vector<string> answer = players;
    for(int i=0; i<players.size(); i++) {
        ranks[players[i]] = i;
    }
    for(auto call : callings) {
        int before_rank = ranks[call];
        int now_rank = before_rank - 1;
        string win_player = call;
        string lose_player = answer[now_rank];
        answer[before_rank] = lose_player;
        answer[now_rank] = win_player;
        ranks[lose_player] = before_rank;
        ranks[win_player] = now_rank;
    }
    return answer;
}