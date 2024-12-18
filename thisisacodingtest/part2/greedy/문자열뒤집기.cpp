#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    string str; cin>>str;
    int one_cnt = 0, zero_cnt = 0, check_point = -1;
    for(int i=0; i<str.size(); i++) {
        int num = str[i] - '0';
        if (check_point != num) {
            check_point = num;
            if (num == 1) one_cnt ++;
            else zero_cnt ++;
        }
    }
    //cout<<zero_cnt<<" "<<one_cnt<<"\n";
    cout<<min(zero_cnt, one_cnt);
}