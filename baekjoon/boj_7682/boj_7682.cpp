#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
char map[3][3];
void moveToMap(string str){
    int cnt=0;
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            map[i][j] = str[cnt++];
        }
    }
}
char whoIsWinner(){
    bool Xwin=false, Owin=false;
    // 일자 방향으로 맞는 것들
    for(int a=0; a<3; a++){
        if (map[a][1] == map[a][0] && map[a][1] == map[a][2]) {
            if (map[a][1] == 'X') Xwin=true;
            else if (map[a][1] == 'O')Owin=true;
        }
        if (map[1][a] == map[0][a] && map[1][a] == map[2][a]) {
            if (map[1][a] == 'X') Xwin=true;
            else if (map[a][1] == 'O') Owin=true;
        }
    }
    //대각선 방향
    if (map[0][0]==map[1][1] && map[1][1]==map[2][2]) {
        if (map[1][1] == 'X') Xwin=true;
        else if (map[1][1] == 'O')Owin=true;
    }
    if (map[0][2]==map[1][1] && map[1][1]==map[2][0]) {
        if (map[1][1] == 'X') Xwin=true;
        else if (map[1][1] == 'O')Owin=true;
    }
    if (Owin && Xwin) return 'f';
    if (Owin) return 'O';
    if (Xwin) return 'X';
    return '.';
}
bool isCorrect(char winner){
    if (winner == 'f') return false;
    int countX=0, countO=0;
    for(int i=0; i<9; i++){
        int y=i/3;
        int x=i%3;
        if (map[y][x] == 'X') countX++;
        else if (map[y][x] == 'O') countO++;
    }
    if (winner == '.' && countX == 5 && countO == 4) return true;
    else if (winner == 'X' && countX == countO+1) return true;
    else if (winner == 'O' && countX == countO) return true;
    return false;
}
int main(){
    string str;
    cin>>str;
    while(str!="end"){
        moveToMap(str);
        if (isCorrect(whoIsWinner())) cout<<"valid\n";
        else cout<<"invalid\n";
        cin>>str;
    }
}