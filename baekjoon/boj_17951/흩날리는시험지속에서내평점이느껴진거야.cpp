#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

int score_cnt, group_cnt;
vector<int> scores;

int main() {
    cin>>score_cnt>>group_cnt;
    for(int i=0; i<score_cnt; i++) {
        int score; cin>>score;
        scores.push_back(score);
    }
    //sort(scores.begin(), scores.end());

    int left = 0, right = accumulate(scores.begin(), scores.end(), 0);
    int answer = 0;
    while(left <= right) {
        int mid = (left + right) / 2;
        int cnt = 0, sum = 0;
        for(int i=0; i<scores.size(); i++) {
            sum += scores[i];
            if (sum >= mid) {
                sum = 0;
                cnt++;
            }
        }
        if (cnt >= group_cnt) {
            left = mid + 1;
            answer = max(answer, mid);
        }
        else right = mid - 1;
    }
    cout<<answer;
}