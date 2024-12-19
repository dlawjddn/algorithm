#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

string make_str(int cnt, string str) {
    return ((cnt <= 1) ? str : to_string(cnt) + str);
}

int solution(string s) {
    int answer = s.size();
    for(int len = 1; len<=s.size()/2; len++) {
        string result = "";
        string temp = "";
        int conti_cnt = 0;
        int pos = 0;
        while(pos < s.size()){
            if (temp != s.substr(pos, len)) {
                result += make_str(conti_cnt, temp);
                conti_cnt = 1;
                temp = s.substr(pos, len);
            } else conti_cnt++;
            pos += len;
        }
        result += make_str(conti_cnt, temp);
        //cout<<result<<"\n";
        answer = min(answer, (int)result.size());
    }
    
    return answer;
}