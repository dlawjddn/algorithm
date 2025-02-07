#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int origin, cnt; cin>>origin>>cnt;
    int buy = 0;
    while(1) {
        int num = origin + buy;
        int group = 0;
        while(num > 0) {
            if (num % 2 != 0) {
                group++;
            }
            num /= 2;
        }
        if (group <= cnt) break;
        buy++;
    }
    cout<<buy;
}