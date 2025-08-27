#include <iostream>
#include <cmath>

using namespace std;

int N, r, c;

int main() {
    cin >> N >> r >> c;

    int ans = 0;
    int n = N;
    while (n > 0) {
        int half = pow(2, n-1);
        int block = half * half;  
        int quad = (r >= half) * 2 + (c >= half);

        ans += quad * block;

        if (r >= half) r -= half;
        if (c >= half) c -= half;
        n--;
    }
    cout << ans;
    return 0;
}
