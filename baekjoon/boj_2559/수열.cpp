#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> arr;
vector<int> acc;
int answer = -1e9;

int main() {
    int arr_size, days; cin>>arr_size>>days;
    for(int i=0; i<arr_size; i++) {
        int num; cin>>num;
        arr.push_back(num);
    }
    for(int i=0; i<arr_size; i++) {
        if(i == 0) acc.push_back(arr[i]);
        else acc.push_back(acc[i-1] + arr[i]);
    }
    for(int i=0; i<arr_size - days + 1; i++) {
        int start = acc[i];
        int end = acc[i + days - 1];
        int temp = end - start + arr[i];
        answer = max(answer, temp);
    }
    cout<<answer;
}