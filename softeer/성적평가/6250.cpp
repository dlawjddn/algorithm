#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int person_cnt = 0;
vector<pair<int, int> > total_score(100000, make_pair(0, 0));

void print_score(vector<pair<int, int> > scores){
    for(int i=0; i<scores.size(); i++){
        cout << scores[i].first << " " << scores[i].second << "\n";
    }
    cout << "\n";
}

int main(int argc, char** argv)
{
    cin >> person_cnt;
    for(int i = 0; i < 3; i++){
        vector<pair<int, int> > scores;
        for(int s = 0; s < person_cnt; s++){
            int score = 0;
            cin >> score;
            scores.push_back(make_pair(score, s));
            total_score[s].first += score;
            total_score[s].second = s;
        }
        vector<pair<int, int> > temp_scores = scores;
        sort(temp_scores.begin(), temp_scores.end(), greater<pair<int, int> >());
        vector<int> result(person_cnt);
        int rank = 1;
        for(int a = 0; a < person_cnt; a++){
            if(a > 0 && temp_scores[a].first == temp_scores[a-1].first){
                result[temp_scores[a].second] = result[temp_scores[a-1].second];
            } else {
                result[temp_scores[a].second] = rank;
            }
            rank++;
        }
        for(int a = 0; a < result.size(); a++){
            cout << result[a] << " ";
        }
        cout << "\n";
    }

    vector<pair<int, int> > temp_scores = total_score;
    sort(temp_scores.begin(), temp_scores.end(), greater<pair<int, int> >());
    vector<int> result(person_cnt);
    int rank = 1;
    for(int a = 0; a < person_cnt; a++){
        if(a > 0 && temp_scores[a].first == temp_scores[a-1].first){
            result[temp_scores[a].second] = result[temp_scores[a-1].second];
        } else {
            result[temp_scores[a].second] = rank;
        }
        rank++;
    }
    for(int a = 0; a < result.size(); a++){
        cout << result[a] << " ";
    }
}

/**
 * @file 성적평가_6250.cpp
 * @brief [HSAT 5회 정기 코딩 인증평가 기출] 성적 평가
 * @version 0.1
 * @date 2024-08-26
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

int people_cnt = 0;
vector<vector<int> > total_scores;
vector<vector<int> > total_rank;
vector<int> sum_score;

bool compare(int a, int b) {
    return a > b;
}

int main(int argc, char** argv){
    cin>>people_cnt;
    total_scores.resize(3, vector<int>(people_cnt, 0));
    total_rank.resize(3, vector<int>(people_cnt, 0));
    sum_score.resize(people_cnt, 0);
    for(int i=0; i<3; i++) {
        for(int j=0; j<people_cnt; j++) {
            cin>>total_scores[i][j];
            sum_score[j] += total_scores[i][j];
        }
    }
    for(int i=0; i<3; i++) {
        set<int, greater<int> > s(total_scores[i].begin(), total_scores[i].end());
        vector<int> result(people_cnt, 0);
        int rank = 1;
        for(auto score : s) {
            int cnt = 0;
            for(int j=0; j<people_cnt; j++) {
                if (total_scores[i][j] == score) {
                    result[j] = rank;
                    cnt++;
                }
            }
            rank += cnt;
        }
        total_rank[i] = result;
    }
    set<int, greater<int> > s(sum_score.begin(), sum_score.end());
    vector<int> result(people_cnt, 0);
    int rank = 1;
    for(auto score : s) {
        int cnt = 0;
        for(int j=0; j<people_cnt; j++) {
            if (sum_score[j] == score) {
                result[j] = rank;
                cnt++;
            }
        }
        rank += cnt;
    }
    total_rank.push_back(result);
    for(int i=0; i<=3; i++) {
        for(int j=0; j<people_cnt; j++) {
            cout<<total_rank[i][j]<<" ";
        }
        cout<<"\n";
    }
}
