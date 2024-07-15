/**
 * @file boj_1062.cpp
 * @brief 백준 gold4 가르침
 * @version 0.1
 * @date 2024-07-15
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>
#include <vector>

using namespace std;

int str_cnt, teach_cnt, answer = 0;
vector<string> words;
vector<bool> alphabets(26, false);

void print_alphabets(){
    for(auto alphabet : alphabets) cout<<alphabet<<" ";
    cout<<"\n";
}

int read_words() {
    int cnt = 0;
    for(auto word : words) {
        int cant_read = false;
        for(int i=4; i<word.size() -4; i++) {
            if (!alphabets[word[i] - 'a']) {
                cant_read = true;
                break;
            }
        }
        if (!cant_read) cnt++;
    }
    return cnt;
}


void dfs(int idx, int cnt) {
    if (cnt == teach_cnt - 5) {
        answer = max(answer, read_words());
        return ;
    }
    for(int i=idx; i<26; i++) {
        if (alphabets[i]) continue;
        alphabets[i] = true;
        dfs(i, cnt + 1);
        alphabets[i] = false;
    }
}

int main(){
    cin>>str_cnt>>teach_cnt;
    words.resize(str_cnt);
    for(int i=0; i<str_cnt; i++) cin>>words[i];
    if (teach_cnt < 5) {
        cout<<"0";
        return 0;
    }
    alphabets['a' - 'a'] = true;
    alphabets['n' - 'a'] = true;
    alphabets['t' - 'a'] = true;
    alphabets['i' - 'a'] = true;
    alphabets['c' - 'a'] = true;
    dfs(0, 0);
    cout<<answer;
}