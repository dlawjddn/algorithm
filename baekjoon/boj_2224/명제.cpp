#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int sentence_cnt;
vector<vector<bool> > maps(52, vector<bool>(52, false));

int convert_alpha(char alpha) {
    if (alpha >= 'A' && alpha <= 'Z') return alpha - 'A';
    return alpha - 'a' + 26;
}

char convert_number(int num) {
    if (num >= 0 && num < 26) return 'A' + num;
    return 'a' + num - 26;
}

int main() {
    cin>>sentence_cnt; cin.ignore();
    for(int i=0; i<sentence_cnt; i++) {
        string s; getline(cin, s);
        int idx1 = convert_alpha(s[0]);
        int idx2 = convert_alpha(s[5]);
        if (idx1 == idx2) continue;
        maps[idx1][idx2] = true;
    }
    for(int i=0; i<52; i++) {
        for(int j=0; j<52; j++) {
            for(int k=0; k<52; k++) {
                if (j == i || i == k || j == k) continue;
                if (maps[j][i] && maps[i][k]) maps[j][k] = true;
            }
        }
    }
    vector<string> answer;
    for(int i=0; i<52; i++) {
        for(int j=0; j<52; j++) {
            if (i == j) continue;
            if (maps[i][j]) {
                answer.push_back(string(1, convert_number(i)) + " => " + string(1, convert_number(j)));
            }
        }
    }
    cout<<answer.size()<<"\n";
    for(int i=0; i<answer.size(); i++) {
        cout<<answer[i]<<"\n";
    }
}