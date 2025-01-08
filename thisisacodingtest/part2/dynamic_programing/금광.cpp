#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int sizeY, sizeX, moveY[3]={-1,0,1}, moveX[3]={1,1,1};
vector<vector<int> > maps;

void print_maps() {
    for(int y=0; y<sizeY; y++) {
        for(int x=0; x<sizeX; x++) {
            cout<<maps[y][x]<<" ";
        }
        cout<<"\n";
    }
    cout<<"\n\n";
}

void print_dp(vector<vector<int> >& dp) {
    for(int y=0; y<sizeY; y++) {
        for(int x=0; x<sizeX; x++) {
            cout<<dp[y][x]<<" ";
        }
        cout<<"\n";
    }
}

bool check_outside(int y, int x) {
    return y < 0 || y >= sizeY || x < 0 || x >= sizeX;
}

int dp() {
    int answer = 0;
    vector<vector<int> > dp = maps;
    for(int x=0; x<sizeX-1; x++) {
        for(int y=0; y<sizeY; y++) {
            for(int d=0; d<3; d++) {
                int ny = y + moveY[d];
                int nx = x + moveX[d];
                if (check_outside(ny, nx)) continue;
                // 이전에 누적되어 있는 값 + 현재의 값
                dp[ny][nx] = max(dp[ny][nx], dp[y][x] + maps[ny][nx]);
            }
        }
    }
    for(int y=0; y<sizeY; y++) {
        answer = max(answer, dp[y][sizeX-1]);
    }
    return answer;
}

int main() {
    int test_case; cin>>test_case;
    for(int t=0; t<test_case; t++) {
        cin>>sizeY>>sizeX;
        maps = vector<vector<int> >(sizeY, vector<int>(sizeX, 0));
        for(int i=0; i<(sizeY * sizeX); i++) {
            int value; cin>>value;
            maps[i / sizeX][i % sizeX] = value;
        }
        //print_maps();
        cout<<dp()<<"\n";
    }
}