#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int chapter_cnt, limit_time;
vector<int> study_times;
vector<int> scores;

int main() {
    cin>>chapter_cnt>>limit_time;
    for(int i=0; i<chapter_cnt; i++) {
        int study_time, score; cin>>study_time>>score;
        study_times.push_back(study_time);
        scores.push_back(score);
    }
    vector<vector<int> > dp(chapter_cnt + 1, vector<int>(limit_time + 1, 0));

    for(int i=1; i<=chapter_cnt; i++) {
        for(int j=0; j<=limit_time; j++) {
            if (j < study_times[i - 1]) {
                dp[i][j] = dp[i-1][j];
            } else {
                dp[i][j] = max(dp[i-1][j], dp[i-1][j - study_times[i-1]] + scores[i-1]);
            }
        }
    }
    cout<<dp[chapter_cnt][limit_time];

}