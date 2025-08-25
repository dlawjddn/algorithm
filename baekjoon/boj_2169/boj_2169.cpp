#include <iostream>
#include <vector>
#include <algorithm>

#define NEG_INF -987654321

using namespace std;

int sizeY, sizeX;
vector<vector<int> > maps;
vector<vector<int> > dp;

int main() {
    cin>>sizeY>>sizeX;
    maps.resize(sizeY, vector<int>(sizeX, 0));
    dp.resize(sizeY, vector<int>(sizeX, NEG_INF));

    for (int y = 0; y < sizeY; y++) {
        for (int x = 0; x < sizeX; x++) cin >> maps[y][x];
    }

    dp[0][0] = maps[0][0];
    for (int x = 1; x < sizeX; x++) dp[0][x] = dp[0][x-1] + maps[0][x];
    for (int y = 1; y < sizeY; y++) {
        vector<int> left(sizeX, NEG_INF), right(sizeX, NEG_INF);

        left[0] = dp[y-1][0] + maps[y][0];
        for (int x = 1; x < sizeX; x++) {
            left[x] = max(left[x-1], dp[y-1][x]) + maps[y][x];
        }

        right[sizeX - 1] = dp[y-1][sizeX - 1] + maps[y][sizeX - 1];
        for (int x = sizeX - 2; x >= 0; x--) {
            right[x] = max(right[x + 1], dp[y-1][x]) + maps[y][x];
        }

        for (int x = 0; x < sizeX; x++) {
            dp[y][x] = max(left[x], right[x]);
        }
    }

    cout<<dp[sizeY - 1][sizeX - 1];
}
