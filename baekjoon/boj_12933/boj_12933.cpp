#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>

using namespace std;

unordered_map<char, int> converter;

vector<int> counts(5, 0);

void print_counts() {
    for(int i=0; i<counts.size(); i++) cout<<counts[i]<<" ";
    cout<<"\n";
}

void init() {
    converter['q'] = 0;
    converter['u'] = 1;
    converter['a'] = 2;
    converter['c'] = 3;
    converter['k'] = 4;
}

bool check_correct(string sound) {
    for(int i=1; i<5; i++) {
        if (counts[i-1] < counts[i]) return false;
    }
    return true;
}

void minus_counts() {
    for(int i=0; i<counts.size(); i++) counts[i] -= 1;
}

int main(){
    int answer = 0;
    string sound; cin>>sound;
    init();
    for(int i=0; i<sound.size(); i++) {
        char alpha = sound[i];
        int idx = converter[alpha];
        counts[idx] += 1;
        if (!check_correct(sound)) {
            cout<<"-1";
            return 0;
        }
        if (alpha == 'k') {
            //print_counts();
            answer = max(answer, *max_element(counts.begin(), counts.end()));
            minus_counts();
        }
    }
    if (*max_element(counts.begin(), counts.end()) != 0) cout<<"-1";
    cout<<answer;
}