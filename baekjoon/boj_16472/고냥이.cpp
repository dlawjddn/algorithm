#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> alpha(26, 0);

int cnt() {
    int result = 0;
    for(int i=0; i<alpha.size(); i++) {
        result += ((alpha[i] > 0) ? 1 : 0);
    }
    return result;
}

int main() {
    int limit; cin>>limit;
    string str; cin>>str;
    int left = 0, right = 0, answer = 0;
    alpha[str[0] - 'a']++;
    while(right < str.size()) {
        int cnt_alpha = cnt();
        if (cnt_alpha <= limit) {
            answer = max(answer, right - left + 1);
            right++;
            alpha[str[right] - 'a']++;
        } else {
            alpha[str[left] - 'a']--;
            left++;
        }
    }
    cout<<answer;
}