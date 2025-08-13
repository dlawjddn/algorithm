#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

char symbols[3] = {'+', '-', ' '};
vector<string> answer;

void check_zero(string str) {
    int num = 0, result = 0, last_sign = 0;
    for(int i=0; i<str.size(); i++) {
        if (str[i] == '+' || str[i] == '-') {
            if (last_sign == 0) result += num;
            else result -= num;

            if (str[i] == '+') last_sign = 0;
            else if (str[i] == '-') last_sign = 1;

            num = 0;
        }
        else if (str[i] == ' ') continue;
        else {
            // 숫자
            num = num * 10 + (str[i] - '0');
        }
    }

    if (last_sign == 0) result += num;
    else result -= num;

    if (result == 0) answer.push_back(str);
}

void dfs(int limit, int num, string str) {
    str += to_string(num);
    if (limit == num) {
        check_zero(str);
        return ;
    }
    for(int x=0; x<3; x++) {
        dfs(limit, num + 1, str + symbols[x]);
    }
}

int main() {
    int test_case; cin>>test_case;
    for(int t=0; t<test_case; t++) {
        int limit; cin>>limit;
        answer = vector<string>();

        dfs(limit, 1, "");
        
        sort(answer.begin(), answer.end());

        for(int i=0; i<answer.size(); i++) cout<<answer[i]<<'\n';
        cout<<"\n";
    }
}