#include <string>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

int moveY[2]={1, 1}, moveX[2]={0, 1};


int solution(vector<vector<int>> triangle) {
    vector<vector<int> > dp = triangle;
    for(int y=0; y<triangle.size() - 1; y++) {
        for(int x=0; x<triangle[y].size(); x++) {
            for(int d=0; d<2; d++) {
                int ny = y + moveY[d];
                int nx = x + moveX[d];
                if (ny < 0 || ny >= triangle.size() || nx < 0 || nx >= triangle[ny].size()) continue;
                dp[ny][nx] = max(dp[ny][nx], dp[y][x] + triangle[ny][nx]);
            }
        }
    }
    return *max_element(dp[triangle.size()-1].begin(), dp[triangle.size()-1].end());
}