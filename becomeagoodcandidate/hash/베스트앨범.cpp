#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

struct Info {
    int idx, play_cnt;
    string genre;
};
vector<Info> infos;
unordered_map<string, int> genre_play_cnt;

bool compare(Info info1, Info info2) {
    if (genre_play_cnt[info1.genre] == genre_play_cnt[info2.genre]) {
        if (info1.play_cnt == info2.play_cnt) return info1.idx < info2.idx;
        return info1.play_cnt > info2.play_cnt;
    } 
    return genre_play_cnt[info1.genre] > genre_play_cnt[info2.genre];
}

vector<int> solution(vector<string> genres, vector<int> plays) {
    vector<int> answer;
    for(int i=0; i<genres.size(); i++) {
        infos.push_back({i, plays[i], genres[i]});
        genre_play_cnt[genres[i]] += plays[i];
    }
    sort(infos.begin(), infos.end(), compare);
    unordered_map<string, int> checker;
    
    for(int i=0; i<infos.size(); i++) {
        if (checker[infos[i].genre] < 2) {
            answer.push_back(infos[i].idx);
            checker[infos[i].genre]++;
        } else continue;
    }
    return answer;
}