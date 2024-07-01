#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int total_test = 0;
vector<vector<int> > alphas;
vector<vector<int> > counts;


void print_alphas(){
    for(int a=0; a<alphas.size(); a++) {
        cout<<(char) (a + 'a')<<": ";
        for(int b=0; b<alphas[a].size(); b++) {
            cout<<alphas[a][b]<<" ";
        }
        cout<<"\n";
    }
}

void print_counts(string str) {
    for(int i=0; i<str.size(); i++) {
        for(int j=0; j<counts[i].size(); j++) {
            cout<<counts[i][j]<<" ";
        }
        cout<<"\n";
    }
}

int find_shortest_str(int cnt) {
    int length = 987654321;
    for(int i=0; i<alphas.size(); i++) {
        if (alphas[i].size() < cnt) continue;
        for(int j=0; j<alphas[i].size() - (cnt - 1); j++) {
            int temp_len = alphas[i][j+cnt-1] - alphas[i][j];
            length = min(length, temp_len);
        }
    }
    if (length == 987654321) return -1;
    return length + 1;
}

bool is_match(int start, int end, int cnt, int alpha_idx) {
    char alpha = alpha + 'a';
    if (start == 0) {
        if (counts[end][alpha_idx] == cnt) return true;
    } else {
        if (counts[end][alpha_idx] - counts[start - 1][alpha_idx] == cnt) return true;
    }
    return false;
}

int find_longest_str(int cnt) {
    int length = 0;
    if (cnt == 1) {
        return 1;
    }
    for(int i=0; i<alphas.size(); i++) {
        if (alphas[i].size() < 2) continue;
        for(int j=0; j<alphas[i].size(); j++) {
            for(int k = j+1; k<alphas[i].size(); k++) {
                int start = alphas[i][j];
                int end = alphas[i][k];
                if (is_match(start, end, cnt, i)) {
                    length = max(length, end - start);
                }
            }
        }
    }
    if (length == 0) return -1;
    return length + 1;
}

int main(){
    cin>>total_test;
    for(int i=0; i<total_test; i++) {
        string str; cin>>str;
        int char_cnt; cin>>char_cnt;

        // 테스트케이스 마다 벡터 초기화
        alphas = vector<vector<int> >(26);
        counts = vector<vector<int> >(str.size(), vector<int>(26, 0));

        for(int j=0; j<str.size(); j++) {
            // 알파벳의 위치 저장
            alphas[str[j] - 'a'].push_back(j);
            // 알파벳의 누적합 저장
            if (j != 0) counts[j] = counts[j-1];
            counts[j][str[j] - 'a'] += 1;
        }
        // print_alphas();
        // cout<<"\n";
        // cout<<"\n";
        // print_counts(str);
        // cout<<"\n";
        int short_len = find_shortest_str(char_cnt);
        if (short_len == -1) {
            cout<<"-1";
            return 0;
        }
        cout<<short_len<<" "<<find_longest_str(char_cnt);
    }
}