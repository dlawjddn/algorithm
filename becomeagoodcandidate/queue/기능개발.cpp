#include <string>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;

vector<int> solution(vector<int> progresses, vector<int> speeds) {
    vector<int> answer;
    for(int i=0; i<progresses.size(); i++) {
        int rest_work = 100 - progresses[i];
        int rest_day = rest_work / speeds[i];
        rest_day += (rest_work % speeds[i] == 0) ? 0 : 1;
        
        pq.push({i, rest_day});
    }
    while(!pq.empty()) {
        auto[idx, deploy_day] = pq.top(); pq.pop();
        int cnt = 1;
        while(!pq.empty() && pq.top().second <= deploy_day) {
            pq.pop(); cnt++;
        }
        answer.push_back(cnt);
    }
    return answer;
}