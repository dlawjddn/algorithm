#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int sq_size; cin>>sq_size;
    vector<vector<int> > maps(sq_size, vector<int>(sq_size, 0));
    int left = 987654321, right = -1;
    long long sum = 0;
    for(int y=0; y<sq_size; y++) {
        for(int x=0; x<sq_size; x++) {
            cin>>maps[y][x];
            left = min(left, maps[y][x]);
            right = max(right, maps[y][x]);
            sum += maps[y][x];
        }
    }

    long long half = (sum % 2 == 0) ? sum / 2 : sum / 2 + 1;

    int answer = right;
    left = 0;
    while(left <= right) {
        int mid = (left + right) / 2;
        long long cnt = 0;
        for(int y=0; y<sq_size; y++) {
            for(int x=0; x<sq_size; x++) {
                cnt += min((long long)maps[y][x], (long long)mid);
            }
        }
        if (cnt < half) left = mid + 1;
        else {
            answer = min(answer, mid);
            right = mid - 1;
        }
    }
    cout<<answer;

}