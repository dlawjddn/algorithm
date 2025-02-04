#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

string dfs(string str) {
    for(int i=0; i<str.size() - 2 && str.size() >= 3; i++) {
        if (str[i] == 'A' && str[i+1] == 'B' && str[i+2] == 'B') {
            string first = str.substr(0, i);
            string changed = "BA";
            string last = ((str.size() < 3) ? "" : str.substr(i+3));
            return dfs(first + changed + last);
        }
    }
    return str;
}

int main() {
    int test_case; cin>>test_case;
    for(int t=0; t<test_case; t++) {
        int size; cin>>size;
        string str; cin>>str;
        cout<<dfs(str)<<"\n";
    }
}