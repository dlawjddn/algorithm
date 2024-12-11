#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int posY, posX;
int moveY[8]={-2, -1, 1, 2, 2, 1, -1, -2}, moveX[8]={-1, -2, -2, -1, 1, 2, 2, 1};

bool check_outside(int y, int x) {
    return y < 1 || y >= 8 || x < 1 || x >= 8;
}

void get_pos(string pos) {
    posY = pos[0] - 'a' + 1;
    posX = pos[1] - '0';
}

int main() {
    int result = 0;
    string pos; cin>>pos;
    get_pos(pos);
    for(int d=0; d<8; d++) {
        int ny = posY + moveY[d];
        int nx = posX + moveX[d];
        if (check_outside(ny, nx)) continue;
        result += 1;
    }
    cout<<result;
}