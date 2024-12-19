#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    string str; cin>>str;
    int left = 0, right = 0;
    for(int i=0; i<str.size(); i++) {
        if (i < str.size() / 2) left += (str[i] - '0');
        else right += (str[i] - '0');
    }
    cout<<((left == right) ? "LUCKY" : "READY");
}