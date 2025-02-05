#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    string origin; cin>>origin;
    vector<bool> check(origin.size() + 1, false);
    
    int word_cnt; cin>>word_cnt;
    vector<string> words;
    for(int i=0; i<word_cnt; i++) {
        string word; cin>>word;
        words.push_back(word);
    }

    for(int i=0; i<origin.size(); i++) {
        if (check[i] || i == 0) {
            for(int j=0; j<words.size(); j++) {
                string word = words[j];
                string compare = origin.substr(i, word.size());
                if (origin.size() < i + word.size()) continue;
                if (word == compare) {
                    check[i + word.size()] = true;
                }
            }
        }
    }
    cout<<check.back();
}