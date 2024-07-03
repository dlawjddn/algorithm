/**
 * @file boj_2493.cpp
 * @brief 백준 gold5 탑
 * @version 0.1
 * @date 2024-07-03
 * 
 * @copyright Copyright (c) 2024
 * 
 * 스택!!
 * 
 */
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

int cnt = 0;
stack<pair<int, int> > s;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin>>cnt;
    for(int i=1; i<=cnt; i++) {
        int height; cin>>height;
        while(!s.empty()) {
            if (s.top().second > height) break;
            s.pop();
        }
        if (s.empty()) cout<<"0 ";
        else cout<<s.top().first<<" ";
        s.push(make_pair(i, height));
    }
}