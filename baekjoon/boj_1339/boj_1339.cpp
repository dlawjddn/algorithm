/**
 * @file boj_1339.cpp
 * @brief 백준 gold4 단어 수학
 * @version 0.1
 * @date 2024-07-20
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;
int answer = 0;
set<char> s;
vector<string> strs;
vector<int> numbers(26, 0);

void print_alphas(vector<char> alphas) {
    for(auto c : alphas) cout<<c<<" ";
    cout<<"\n";
}

int add_strings() {
    int sum = 0;
    for(auto str : strs) {
        int num = 0;
        for(int i=0; i<str.size(); i++) {
            num = num * 10 + numbers[str[i] - 'A'];
        }
        sum += num;
    }
    return sum;
}

int main(){
    int str_cnt; cin>>str_cnt;
    strs.resize(str_cnt);
    for(int i=0; i<str_cnt; i++) {
        cin>>strs[i];
        for(int j=0; j<strs[i].size(); j++) {
            s.insert(strs[i][j]);
        }
    }
    vector<char> alphas(s.begin(), s.end());
    do {
        int num = 9;
        for(auto alpha : alphas) {
            numbers[alpha - 'A'] = num--;
        }
        answer = max(answer, add_strings());
    }while(next_permutation(alphas.begin(), alphas.end()));
    cout<<answer;
}