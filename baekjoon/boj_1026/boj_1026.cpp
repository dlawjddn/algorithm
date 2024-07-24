/**
 * @file boj_1026.cpp
 * @brief 백준 silver4 보물
 * @version 0.1
 * @date 2024-07-24
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Compare {
    bool operator()(int n1, int n2) {
        return n1 > n2;
    }
};
int arr_size, answer = 0;
vector<int> num1;
vector<int> num2;

void print_numbers(){
    for(auto n : num1) cout<<n<<" ";
    cout<<"\n";
    for(auto n : num2) cout<<n<<" ";
    cout<<"\n";
}

int main(){
    cin>>arr_size;
    num1.resize(arr_size);
    num2.resize(arr_size);
    for(int i=0; i<arr_size; i++) cin>>num1[i];
    for(int i=0; i<arr_size; i++) cin>>num2[i];
    sort(num1.begin(), num1.end());
    sort(num2.begin(), num2.end(), Compare());
    for(int i=0; i<arr_size; i++) {
        answer += (num1[i] * num2[i]);
    }
    cout<<answer;
}