#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

int sushi_cnt, kind_of_sushi, discount, service, answer = 0;
vector<int> sushies;
unordered_map<int, int> eat;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin>>sushi_cnt>>kind_of_sushi>>discount>>service;
    for(int i=0; i<sushi_cnt; i++) {
        int sushi; cin>>sushi;
        sushies.push_back(sushi);
    }
    for(int i=0; i<discount; i++) {
        sushies.push_back(sushies[i % sushies.size()]);
    }
    eat[service]++;
    int unique_cnt = 1;
    for(int i=0; i<discount; i++) {
        if (eat[sushies[i]] == 0) unique_cnt++;
        eat[sushies[i]]++;
    }
    answer = max(answer, unique_cnt);
    for(int i=discount; i<sushi_cnt + discount; i++) {
        int delete_idx = i - discount;
        int delete_sushi = sushies[delete_idx];
        eat[delete_sushi]--;
        if (eat[delete_sushi] == 0) unique_cnt--;

        if (eat[sushies[i]] == 0) unique_cnt++;
        eat[sushies[i]]++;

        answer = max(answer, unique_cnt);
    }
    cout<<answer;
}