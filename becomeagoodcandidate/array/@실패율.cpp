#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

bool compare(pair<double, int> p1, pair<double, int> p2) {
    if (p1.first == p2.first) return p1.second < p2.second;
    return p1.first > p2.first;
}

vector<int> solution(int N, vector<int> stages) {
    vector<int> answer;
    sort(stages.begin(), stages.end());
    
    vector<pair<double, int> > result;
    int idx = 0, total_challenger = stages.size();
    for(int stage = 1; stage <= N; stage++) {
        int cnt = 0;
        while(idx < stages.size() && stages[idx] == stage) {
            cnt++;
            idx++;
        }
        result.push_back({((double) cnt / (double)total_challenger), stage});
        total_challenger -= cnt;
    }
    sort(result.begin(), result.end(), compare);
    
    for(int i=0; i<result.size(); i++) {
        answer.push_back(result[i].second);
        //cout<<result[i].second<<" stage ";
        //cout<<result[i].first<<"\n";
    }
    return answer;
}