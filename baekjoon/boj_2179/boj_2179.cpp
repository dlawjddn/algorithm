#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int word_cnt;
vector<string> words;
vector<pair<string, int> > sorted_words;
vector<int> prefix_len;

bool compare(pair<int, int> p1, pair<int, int> p2) {
    if (p1.first == p2.first) return p1.second < p2.second;
    return p1.first < p2.first;
}

int cal_prefix_len(string& s1, string& s2) {
    int limit = min(s1.size(), s2.size());
    int len = 0;
    while(len < limit && s1[len] == s2[len]) {
        len++;
    }
    return len;
}

int main() {
    cin>>word_cnt;
    prefix_len.resize(word_cnt, -1);
    for(int i=0; i<word_cnt; i++) {
        string word; cin>>word;
        words.push_back(word);
        sorted_words.push_back({word, i});
    }
    sort(sorted_words.begin(), sorted_words.end());

    int max_len = -1;
    for(int i=0; i<sorted_words.size() - 1; i++) {
        if (sorted_words[i].first == sorted_words[i+1].first) continue; // 같은 문자열인 경우, 생략

        int prefix = cal_prefix_len(sorted_words[i].first, sorted_words[i+1].first);
        prefix_len[i] = prefix;
        max_len = max(max_len, prefix);
    }

    int answer1 = 1e9;
    int answer2 = 1e9;
    for(int i=0; i<prefix_len.size();) {
        if (prefix_len[i] == max_len) {
            int s = i;
            int e = i + 1;
            while(e < prefix_len.size() && prefix_len[e] == max_len) {
                e++;
            }
            // prefix 배열 안에서 max 접두사 길이가 되는 그룹 범위, s~e를 찾음
            int local1 = 1e9, local2 = 1e9;
            for(int j=s; j<=e; j++) {
                int idx = sorted_words[j].second;
                if (idx < local1) {
                    local2 = local1;
                    local1 = idx;
                }
                else if (idx < local2) {
                    local2 = idx;
                }
            }

            if (local1 < answer1 || (local1 == answer1 && local2 < answer2)) {
                answer1 = local1;
                answer2 = local2;
            }
            i = e;
        }
        else i++;
    }
    cout<<words[answer1]<<'\n'<<words[answer2];
}