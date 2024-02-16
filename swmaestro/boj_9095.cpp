// 정수 n을 1,2,3을 통해 만들 수 있는 경우의 수 세기 

// 1 -> 1
// 2 -> 1+1, 2
// 3 -> 1+1+1, 2+1, 1+2, 3
// 4 -> 1+1+1+1, 2+1+1, 1+2+1, 3+1, 1+3 1+2+1, -> 1+3, 2+2, 3+1
// 5 -> 4+1, 3+2, 2+3, 1+4
#include <iostream>
#include <algorithm>
using namespace std;
int num[1000001];
int main(){
    num[1] = 1;
    num[2] = 2;
    num[3] = 4;
    for(int i = 4; i<=10; i++){
        num[i] = num[i-3] + num[i-2] + num[i-1];
    }
    int test = 0;
    cin>>test;
    for(int i=0; i<test; i++){
        int temp = 0;
        cin>>temp;
        cout<<num[temp]<<"\n";
    }
}