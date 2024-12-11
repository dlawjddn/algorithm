#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

int sq_size, posY = 1, posX = 1;

bool check_outside(int y, int x) {
    return !(y >= 1 && y <= sq_size && x >= 1 && x <= sq_size);
}

vector<string> split(string origin, char delimeter) {
    vector<string> result;
    string token;
    istringstream token_stream(origin);
    while(getline(token_stream, token, delimeter)) {
        result.push_back(token);
    }
    return result;
}

/**
 * @brief 입출력으로 장난치는 문제의 대비하기!(python 우대인가? ㅋㅋ 아님 말고~)
 * 
 * 입력의 크기를 주지 않고, 입력을 받아야 하는 경우에는 해당 입력을 문자열로 받아서, 파싱해버리자
 * 이때, getline()을 사용하기 전에 cin으로 입력을 받아야 하는 상황이라면 cin에서 입력받고 버퍼에 남아있는 줄바꿈을 제거하기 위해
 * cin.ignore()를 사용해서 버퍼를 비운 다음에 getline()을 사용하자
 * (비우지 않는다면, 입력이 들어오지 않고, 버퍼에 남아있는 줄바꿈을 인식해서 입력이 종료되어 버림)
 * 
 */

int main() {
    cin>>sq_size;
    cin.ignore();
    string dirs;
    getline(cin, dirs);
    vector<string> splited_dirs = split(dirs, ' ');
    for(int i=0; i<splited_dirs.size(); i++) {
        int ny = posY, nx = posX;
        if (splited_dirs[i] == "L") nx -= 1;
        else if (splited_dirs[i] == "R") nx += 1;
        else if (splited_dirs[i] == "U") ny -= 1;
        else ny += 1;
        if (check_outside(ny, nx)) continue;

        posY = ny; posX = nx;
    }

    cout<<posY<<" "<<posX;
}