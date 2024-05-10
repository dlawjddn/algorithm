#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main(int argc, char** argv)
{
    int len = 0, answer = 1;
    cin>>len;
    vector<int> arr(len);
    vector<int> dp(len, 1);
    for(int i=0; i<len; i++){
        cin>>arr[i];
    }
    for(int i=0; i<len; i++){
        for(int j = i-1; j>=0; j--){
            if (arr[i] > arr[j]){
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
        answer = max(answer, dp[i]);
    }
    cout<<answer;
}