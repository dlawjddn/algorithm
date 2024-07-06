/**
 * @file boj_10451.cpp
 * @brief 백준 silver3 순열 사이클
 * @version 0.1
 * @date 2024-07-06
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<bool> visited;
vector<int> numbers;
void dfs(int pos) {
    visited[pos] = true;
    if (visited[numbers[pos]]) return ;
    dfs(numbers[pos]);
}

int main(){
    int test_case; cin>>test_case;
    for(int i=0; i<test_case; i++) {
        int answer = 0, len; cin>>len;
        numbers = vector<int>(len + 1);
        visited = vector<bool>(len + 1, false);
        for(int i=1; i<=len; i++) cin>>numbers[i];
        for(int i=1; i<=len; i++) {
            if (visited[i]) continue;
            dfs(i);
            answer++;
        }
        cout<<answer<<"\n";
    }
}