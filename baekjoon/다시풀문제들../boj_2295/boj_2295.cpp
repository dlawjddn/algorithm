/**
 * @file boj_2295.cpp
 * @brief 백준 gold4 세 수의 합
 * @version 0.1
 * @date 2025-01-22
 * 
 * @copyright Copyright (c) 2025
 * 
 * 아..
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

using namespace std;

int cnt, answer = - 1;
vector<int> numbers;
unordered_map<int, bool> checker;

int main() {
    cin>>cnt;
    for(int i=0; i<cnt; i++) {
        int num; cin>>num;
        numbers.push_back(num);
        checker[num] = true;
    }
    sort(numbers.begin(), numbers.end());

    unordered_set<int> temp_sum;
    for(int i=0; i<numbers.size(); i++) {
        for(int j=0; j<numbers.size(); j++) {
            temp_sum.insert(numbers[i] + numbers[j]);
        }
    }
    for(int i=cnt-1; i>=0; i--) {
        for(int j=i; j>=0; j--) {
            int target = numbers[i] - numbers[j];
            if (temp_sum.find(target) != temp_sum.end()) {
                cout<<numbers[i];
                return 0;
            }
        }
    }
    
    
    cout<<answer;
}