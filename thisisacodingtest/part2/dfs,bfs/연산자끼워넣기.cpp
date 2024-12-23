#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int num_cnt, min_answer = 1987654321, max_answer = -1987654321;
vector<int> numbers;
vector<char> symbols;

int cal() {
    int result = numbers[0];
    for(int i=1; i<numbers.size(); i++) {
        if (symbols[i-1] == '+') result += numbers[i];
        else if (symbols[i-1] == '-') result -= numbers[i];
        else if (symbols[i-1] == '*') result *= numbers[i];
        else result /= numbers[i];
    }
    return result;
}

int main() {
    cin>>num_cnt;
    for(int i=0; i<num_cnt; i++) {
        int num; cin>>num;
        numbers.push_back(num);
    }
    for(int i=0; i<4; i++) {
        int cnt; cin>>cnt;
        for(int j=0; j<cnt; j++) {
            if (i == 0) symbols.push_back('+');
            else if (i==1) symbols.push_back('-');
            else if (i==2) symbols.push_back('*');
            else symbols.push_back('/');
        }
    }
    sort(symbols.begin(), symbols.end());
    do {
        int result = cal();
        min_answer = min(min_answer, result);
        max_answer = max(max_answer, result);
    }while(next_permutation(symbols.begin(), symbols.end()));

    cout<<max_answer<<"\n"<<min_answer;
}