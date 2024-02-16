// 규칙에 의한 선택하는 경우의 수를 구하는 것을 코드로 나타내기

#include <iostream>
#include <algorithm>
using namespace std;

int stair[301];
int score[301];

int main(){
    int cnt;
    cin>>cnt;
    for(int i=0; i<cnt; i++){
        cin>>stair[i+1];
    }
    score[0] = 0;
    score[1] = stair[1];
    score[2] = stair[1] + stair[2];
    for(int i=3; i<=cnt; i++){
        score[i] = stair[i] + max(score[i-2], stair[i-1] + score[i-3]);
    }
    cout<<score[cnt];
}