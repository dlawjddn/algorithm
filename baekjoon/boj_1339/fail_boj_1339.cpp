#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<char> > digits(10);
vector<string> strs;
vector<bool> check(26, false);
vector<int> numbers(26, -1);

void print_digits(){
    for(int y=0; y<digits.size(); y++) {
        cout<<y<<": ";
        for(int x=0; x<digits[y].size(); x++) {
            cout<<digits[y][x]<<" ";
        }
        cout<<"\n";
    }
}

void print_numbers(){
    for(int i=0; i<numbers.size(); i++) {
        cout<<(char) (i + 'A')<<": "<<numbers[i]<<"\n";
    }
}

void allocate_number(){
    int number = 9;
    for(int y=digits.size() - 1; y >= 0; y--) {
        for(int x=0; x<digits[y].size(); x++) {
            if (check[digits[y][x] - 'A']) continue;
            numbers[digits[y][x] - 'A'] = number--;
            check[digits[y][x] - 'A'] = true;
        }
    }
}

void change_to_number() {
    int answer = 0;
    for(int i=0; i<strs.size(); i++) {
        int num = 0;
        for(int j=0; j<strs[i].size(); j++) {
            num = num * 10 + numbers[strs[i][j] - 'A'];
        }
        answer += num;
    }
    cout<<answer;
}

int main(){
    int str_cnt; cin>>str_cnt;
    for(int i=0; i<str_cnt; i++) {
        string str; cin>>str;
        strs.push_back(str);
        reverse(str.begin(), str.end());
        for(int j=0; j<str.size(); j++) {
            digits[j].push_back(str[j]);
        }
    }
    allocate_number();
    change_to_number();
}