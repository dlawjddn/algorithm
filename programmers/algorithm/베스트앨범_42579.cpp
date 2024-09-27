/**
 * @file 베스트앨범_42579.cpp
 * @brief 프로그래머스 lv.3 베스트 앨범
 * @version 0.1
 * @date 2024-08-17
 * 
 * @copyright Copyright (c) 2024
 * 
 * 레전드 레전드 레전드 사건 발생~
 * vector <--> map 이 가능하다는게 너무 소름이다..
 * vector(x.begin(), x.end()); -> 이게 완~~전히 미친놈
 * 
 * 좋은거 하나 배워간다!!!
 * 
 */
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

bool compare_by_play_count(const pair<string, int>& p1, const pair<string, int>& p2) {
    return p1.second > p2.second;
}

bool compare_by_play_info(const pair<int, int>& p1, const pair<int, int>& p2) {
    if (p1.second == p2.second)
        return p1.first < p2.first;
    return p1.second > p2.second;
}

vector<int> solution(vector<string> genres, vector<int> plays) {
    vector<int> answer;
    unordered_map<string, int> genre_map;
    unordered_map<string, vector<pair<int, int> > > play_map;
    for(int i=0; i<genres.size(); i++) {
        genre_map[genres[i]] += plays[i];
        play_map[genres[i]].push_back({i, plays[i]});
    }
    vector<pair<string, int> > genre_vector(genre_map.begin(), genre_map.end());
    vector<pair<string, vector<pair<int, int> > > > play_vector(play_map.begin(), play_map.end());
    
    sort(genre_vector.begin(), genre_vector.end(), compare_by_play_count);

    for(auto& genre : genre_vector) {
        string genre_name = genre.first;
        vector<pair<int, int>>& plays_info = play_map[genre_name];
        
        sort(plays_info.begin(), plays_info.end(), compare_by_play_info);
        
        for(int i = 0; i < min(2, (int)plays_info.size()); i++) {
            answer.push_back(plays_info[i].first);
        }
    }
    return answer;
}
/**
 * @file 베스트앨범_42579.cpp
 * @brief 프로그래머스 lv.2 베스트앨범
 * @version 0.1
 * @date 2024-09-27
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <iostream>

using namespace std;

unordered_map<string, int> total_play;
unordered_map<string, vector<pair<int, int> > > infos;

bool compare(pair<int, int> p1, pair<int, int> p2) {
    if (p1.first == p2.first) {
        return p1.second < p2.second;
    }
    return p1.first > p2.first;
}

vector<int> solution(vector<string> genres, vector<int> plays) {
    vector<int> answer;
    for(int i=0; i<plays.size(); i++) {
        string genre = genres[i];
        int play = plays[i];
        total_play[genre] += play;
        infos[genre].push_back({play, i});
    }
    vector<pair<int, string> > temp;
    for(auto data : total_play) {
        string genre = data.first;
        int play = data.second;
        temp.push_back({play, genre});
    }
    sort(temp.rbegin(), temp.rend()); // 총 실행 횟수 내림차순
    for(auto t : temp) {
        string genre = t.second;
        vector<pair<int, int> > play_info = infos[genre];
        sort(play_info.begin(), play_info.end(), compare);
        int limit = min(2, (int)play_info.size());
        for(int i=0; i<limit; i++) {
            answer.push_back(play_info[i].second);
        }
    }
    return answer;
}