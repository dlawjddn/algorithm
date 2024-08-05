#include <string>
#include <vector>
#include <sstream>
#include <iostream>

using namespace std;

string solution(string s) {
    string answer = "";
    bool start = true;
    for(int i=0; i<s.size(); i++) {
        if (s[i] == ' ') {
            start = true;
            answer += s[i];
            continue;
        }
        else {
            if (start && s[i] >= 'a' && s[i] <= 'z') {
                answer += s[i] - 'a' + 'A';
                start = false;
                continue;
            }
            if (!start && s[i] >= 'A' && s[i] <= 'Z') {
                answer += s[i] - 'A' + 'a';
                continue;
            }
        }
        answer += s[i];
        start = false;
    }
    return answer;
}