#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int people_cnt;
vector<int> people;
vector<int> dp;

void print_people() {
    for(int i=0; i<people.size(); i++) cout<<people[i]<<" ";
    cout<<"\n";
}

void print_dp() {
    for(int i=0; i<dp.size(); i++) cout<<dp[i]<<" ";
    cout<<"\n";
}

int main() {
    cin>>people_cnt;
    dp.resize(people_cnt + 1, 0);
    people.resize(people_cnt + 1, 0);

    for(int i=0; i<people_cnt; i++) cin>>people[i + 1];

    dp[1] = 1;

    for(int i=2; i<=people_cnt; i++) {
        int max_value = 0;
        for(int j=0; j<i; j++) {
            if (people[j] > people[i]) max_value = max(dp[j], max_value);
        }
        dp[i] = max_value + 1;
    }
    // print_people();
    // print_dp();
    cout<<people_cnt - dp.back();
}