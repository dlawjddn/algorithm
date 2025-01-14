#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <iostream>

using namespace std;

struct Info {
    pair<int, int> start, end;
    bool operator<(const Info& other) const {
        // set을 사용할 때, 모든 요소에 대해서 비교해주지 않으면, 그 요소를 가지고 중복 여부를 판단하기 때문에
        // 이 문제처럼 start와 end에 대해서 모두 파악한 뒤 중복 처리를 해야 하는 경우에는 모든 요소에 대해서 비교 처리가 들어가야 함
        if (start != other.start) {
            return start < other.start;
        }
        return end < other.end;
    }
};
int moveY[4]={0,1,0,-1}, moveX[4]={1,0,-1,0};
set<Info> path;

bool check_outside(int y, int x) {
    return y < -5 || y > 5 || x < -5 || x > 5;
}

int convert_dir(char c) {
    if (c == 'U') return 1;
    else if (c == 'L') return 2;
    else if (c == 'R') return 0;
    else return 3;
}

int solution(string dirs) {
    int y = 0, x = 0;
    for(auto dir : dirs) {
        cout<<y<<" "<<x<<"\n";
        int d = convert_dir(dir);
        int ny = y + moveY[d];
        int nx = x + moveX[d];
        if (check_outside(ny, nx)) continue;
        path.insert({{y, x}, {ny, nx}});
        path.insert({{ny, nx}, {y, x}});
        y = ny; x = nx;
    }
    cout<<path.size()<<"\n";
    return path.size() / 2;
}