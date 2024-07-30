/**
 * @file boj_2805.cpp
 * @brief 백준 silver2 나무 자르기
 * @version 0.1
 * @date 2024-07-30
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int tree_cnt, answer;
long long need;
vector<int> trees;

int main(){
    cin>>tree_cnt>>need;
    trees.resize(tree_cnt);
    for(int i=0; i<tree_cnt; i++) cin>>trees[i];
    sort(trees.begin(), trees.end());
    int left = 0, right = trees.back();
    while(left <= right) {
        int mid = (left + right) / 2;
        long long cut = 0;
        for(int i=0; i<trees.size(); i++) {
            int len = trees[i] - mid;
            if (len <= 0) continue;
            cut += len;
        }
        if (cut >= need) {
            left = mid + 1;
            answer = mid;
        } else right = mid - 1;
    }
    cout<<answer;
}