#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

void print_dp(vector<vector<int> > dp){
    for(int y=0; y<dp.size(); y++){
        for(int x=0; x<dp[y].size(); x++){
            cout<<dp[y][x]<<" ";
        }
        cout<<"\n";
    }
}

int solve(vector<int> elements){
    set<int> answer;
    vector<vector<int> > dp(elements.size(), vector<int>(elements.size(), 0));
    // 1개 선택할 때의 수
    for(int x=0; x<elements.size(); x++){
        dp[0][x] = elements[x];
        answer.insert(dp[0][x]);
    }
    // 2개 이상 선택할 때의 수
    for(int y=1; y<elements.size(); y++){
        for(int x=0; x<elements.size(); x++){
            dp[y][(x+y) % elements.size()] = dp[0][x] + dp[y-1][(x+y) % elements.size()];
            answer.insert(dp[y][(x+y) % elements.size()]);
        }
    }
    return answer.size();
}
int solution(vector<int> elements) {
    return solve(elements);
}