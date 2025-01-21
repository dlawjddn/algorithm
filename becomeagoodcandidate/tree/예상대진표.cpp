#include <iostream>
#include <algorithm>

using namespace std;

int solution(int n, int a, int b){
    if (a > b) swap(a, b);
    int cnt = 1;
    while(n > 1) {
        if (((a / 2) + (a % 2)) == ((b / 2) + (b % 2))) break;
        n /= 2;
        cnt++;
        a = (a % 2 == 0) ? a / 2 : a / 2 + 1;
        b = (b % 2 == 0) ? b / 2 : b / 2 + 1;
    }
    return cnt;
}