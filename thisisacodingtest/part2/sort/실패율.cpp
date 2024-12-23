#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <iostream>

using namespace std;

vector<int> challenge;
vector<pair<double, int> > percentage;

bool compare(pair<double, int> p1, pair<double, int> p2) {
    if (p1.first == p2.first) {
        return p1.second < p2.second;
    }
    return p1.first > p2.first;
}

vector<int> solution(int N, vector<int> stages) {
    vector<int> answer;
    challenge.resize(N+1, 0);
    for(auto stage : stages) {
        if (stage > N) continue;
        challenge[stage] += 1;
    }
    int total_people = stages.size();
    for(int i=1; i<=N; i++) {
        if (challenge[i] == 0) {
            percentage.push_back({0.0, i});
            continue;
        }
        percentage.push_back({(double)challenge[i] / total_people, i});
        total_people -= challenge[i];
    }
    sort(percentage.begin(), percentage.end(), compare);
    for(auto info : percentage) {
        answer.push_back(info.second);
    }
    return answer;
}