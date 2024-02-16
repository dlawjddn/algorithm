// 1 -> 1
// 2 -> 1
// 3 -> 1
// 4 -> 2
// 5 -> 3
// 6 -> 2
// 7 -> 3
// 8 -> 3
// 9 -> 2
// 10 -> 3

// n이 2 또는 3으로 나누어 떨어지는 경우 -> 나눈 값의 몫 + 1
// n이 2 또는 3으로 안 떨어지는 경우 -> arr[n-1] + 1
#include <iostream>
#include <algorithm>
using namespace std;
int arr[1000001];

int main(){
    int n = 0;
    cin>>n;
    for(int i=2; i<=n; i++){
        arr[i] = arr[i-1] + 1;
        if (i % 3 == 0){
            arr[i] = min(arr[i], arr[i/3]+1);
        }
        if (i % 2 == 0){
            arr[i] = min(arr[i], arr[i/2]+1);
        }   
    }
    cout<<arr[n];
}