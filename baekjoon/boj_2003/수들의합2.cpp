#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> arr;

int main() {
    int arr_size, target; cin>>arr_size>>target;
    for(int i=0; i<arr_size; i++) {
        int num; cin>>num;
        arr.push_back(num);
    }
    int left = 0, right = 0, sum = 0, answer = 0;
    while(right <= arr_size) {
        if (sum < target) {
            sum += arr[right++];
        } else if (sum > target) {
            sum -= arr[left++];
        } else {
            answer++;
            sum -= arr[left++];
        }
    }
    cout<<answer;
}