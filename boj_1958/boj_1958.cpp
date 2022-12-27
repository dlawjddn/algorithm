#include <iostream>
#include <algorithm>
using namespace std;
int dp[101][101][101];
int main(){
    string s1;
    string s2;
    string s3;
    cin>>s1>>s2>>s3;
    for(int z=1; z<=s3.length(); z++){
        for(int y=1; y<=s2.length(); y++){
            for(int x=1; x<=s1.length(); x++){
                if (s1[x-1]==s2[y-1] && s2[y-1]==s3[z-1]) dp[y][x][z]=dp[y-1][x-1][z-1]+1;
                else dp[y][x][z]=max(dp[y-1][x][z], max(dp[y][x-1][z], dp[y][x][z-1]));
            }
        }
    }
    cout<<dp[s2.length()][s1.length()][s3.length()];
}
