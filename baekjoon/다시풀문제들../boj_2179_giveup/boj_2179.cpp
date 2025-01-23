#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int str_cnt, answer = 0, idx_left = 0, idx_right = 0;
vector<string> strs;

int compare_strings(string s1, string s2) {
    int cnt = 0, len = min(s1.size(), s2.size());
    for(int i=0; i<len; i++) {
        if (s1[i] == s2[i]) cnt++;
        else return cnt;
    }
    return cnt;
}

int main(){
    cin>>str_cnt;
    for(int i=0; i<str_cnt; i++) {
        string temp; cin>>temp;
        if (find(strs.begin(), strs.end(), temp) == strs.end()) {
            strs.push_back(temp);
        }
    }
    for(int i=0; i<strs.size()-1; i++) {
        string origin = strs[i];
        for(int j=i+1; j<strs.size(); j++) {
            string compare = strs[j];
            int cnt = compare_strings(origin, compare);
            if (answer < cnt) {
                answer = cnt;
                idx_left = i; idx_right = j;
            }
        }
    }
    cout<<strs[idx_left]<<"\n"<<strs[idx_right];
}