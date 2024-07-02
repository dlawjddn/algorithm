#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

int cnt = 0;
vector<int> numbers;
vector<int> dp;
vector<int> before(100001, 0);
vector<vector<int> > idxs(100001);

void print_dp(){
    for(auto value : dp) {
        cout<<value<<" ";
    }
    cout<<"\n";
}

int main(){
    cin>>cnt;
    numbers.resize(cnt);
    dp.resize(cnt);
    for(int i=0; i<cnt; i++) {
        cin>>numbers[i];
        idxs[numbers[i]].push_back(i);
    }
    dp[0] = 1;
    before[numbers[0]] = 1;
    for(int i=1; i<cnt; i++) {
        dp[i] = dp[i-1] + 1;
        if (idxs[numbers[i]][0] != i) {
            dp[i] -= before[numbers[i]];
            idxs[numbers[i]].erase(idxs[numbers[i]].begin());
            before[numbers[i]] = 1;
            continue;
        }
        before[numbers[i]]++;
    }
    //print_dp();
    cout<<accumulate(dp.begin(), dp.end(), 0);
}