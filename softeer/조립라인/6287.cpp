#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>

using namespace std;

int len = 0;
vector<int> a_worktime(1000);
vector<int> b_worktime(1000);
vector<int> a_movetime(1000);
vector<int> b_movetime(1000);
vector<vector<int> > dp(1000, vector<int>(2,0));

void print_dp(){
    for(int y=0; y<len; y++){
        for(int x=0; x<2; x++){
            cout<<dp[y][x]<<" ";
        }
        cout<<"\n";
    }
}

int cal_dp(){
    dp[0][0] = a_worktime[0];
    dp[0][1] = b_worktime[0];
    for(int y=1; y<len; y++){
        // a 공장에서의 최소시간
        // 이전 a에서의 최소 작업 시간 + 현재 a에서의 작업 시간
        // 이전 b에서의 최소 작업 시간 + 현재 a에서의 작업 시간 + 이동 시간
        dp[y][0] = min(dp[y-1][0] + a_worktime[y], dp[y-1][1] + b_movetime[y-1] + a_worktime[y]);
        dp[y][1] = min(dp[y-1][1] + b_worktime[y], dp[y-1][0] + a_movetime[y-1] + b_worktime[y]);
    }
    return min(dp[len-1][0], dp[len-1][1]);
}
int main(int argc, char** argv)
{
    cin>>len;
    for(int i=0; i<len-1; i++){
        cin>>a_worktime[i]>>b_worktime[i]>>a_movetime[i]>>b_movetime[i];
    }
    cin>>a_worktime[len-1]>>b_worktime[len-1];
    cout<<cal_dp();
    //print_dp();
}