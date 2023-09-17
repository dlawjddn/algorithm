#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

struct Sig{
    char s, d;
    int ew, sn;
};
struct Point{
    int y, x, move;
};
char map[20][20][20];
int sizeY[20], sizeX[20], visited[20][20][20], moveX[5]={0,1,0,-1,0}, moveY[5]={0,0,1,0,-1};
Sig sig[20][10];

bool checkBound(int testCase, int y, int x){
    return y>=0 && y<sizeY[testCase] && x>=0 && x<sizeX[testCase];
}

bool checkSignal(int testCase, int y, int x){
    if (map[y - 1][x][testCase] >= '0' && map[y-1][x][testCase] <= '9') return true;
    else if (map[y + 1][x][testCase] >= '0' && map[y + 1][x][testCase] <= '9') return true;
    else if (map[y][x - 1][testCase] >= '0' && map[y][x - 1][testCase] <= '9') return true;
    else if (map[y][x + 1][testCase] >= '0' && map[y][x + 1][testCase]) return true;
    return false;
}

int moving_truck(int testCase, int startY, int startX){
    Point start; start.y=startY; start.x=startX, start.move=0;
    queue<Point> q;
    q.push(start);
    visited[startY][startX][testCase] = 1;
    while(!q.empty()){
        Point now = q.front(); q.pop();
        for(int d=0; d<5; d++){
            Point next;
            next.y=now.y+moveY[d];
            next.x=now.x+moveX[d];
            next.move = now.move + 1;
            if (d == 0 && checkSignal(testCase, next.y, next.x)){ // 머무르는 경우
                Point temp; temp.y=now.y; temp.x = now.x; temp.move = now.move+1;
                q.push(temp);
            }
            else if (checkBound(testCase, next.y, next.x) && map[next.y][next.x][testCase] != '.' && !visited[next.y][next.x][testCase]){
                if (map[next.y][next.x][testCase] == '#'){
                    q.push(next);
                    visited[next.y][next.x][testCase] = visited[now.y][now.x][testCase] + 1;
                }
                else if (map[next.y][next.x][testCase] >= '0' && map[next.y][next.x][testCase] <= '9'){
                    int sign = map[next.y][next.x][testCase] -48; // 신호등 숫자 정수로 변환
                    int timeSum = sig[testCase][sign].ew + sig[testCase][sign].sn;
                    int check = next.move % timeSum;
                    if (sig[testCase][sign].d == '|'){ // sn 방향이 먼저 켜지는 경우
                        if (check <= sig[testCase][sign].sn && check != 0){ // 현재 sn방향에 불이 켜진 경우
                            if (d == 2 || d == 4){
                                q.push(next);
                                visited[next.y][next.x][testCase] = visited[now.y][now.x][testCase] + 1; 
                            }
                        }
                        else{ // sn 방향에 불이 먼저 켜지지만 현재는 ew 방향에 불이 켜짐
                            if (d == 1 || d== 3){
                                q.push(next);
                                visited[next.y][next.x][testCase] = visited[now.y][now.x][testCase] + 1; 
                            }
                        }
                    }
                    else{ // ew 방향이 먼저 켜지는 경우
                        if (check <= sig[testCase][sign].ew && check != 0){ // 현재 ew방향에 불이 켜진 경우
                            if (d == 1 || d == 3){
                                q.push(next);
                                visited[next.y][next.x][testCase] = visited[now.y][now.x][testCase] + 1; 
                            }
                        }
                        else{ // ew 방향에 불이 먼저 켜지지만 현재는 sn 방향에 불이 켜짐
                            if (d == 2 || d== 4){
                                q.push(next);
                                visited[next.y][next.x][testCase] = visited[now.y][now.x][testCase] + 1; 
                            }
                        }
                    }
                }
                else{
                    return next.move;
                }
            }
        }
    }
    return 0;
}

int main(){
    int testCase = 0;
    while(1){
        cin>>sizeY[testCase]>>sizeX[testCase];
        if (sizeY[testCase] == 0 && sizeX[testCase] == 0) break;
        int sCnt = 0, startY=0, startX=0;
        for(int i = 0;  i<sizeY[testCase]; i++){
            string tmp;
            cin>>tmp;
            for(int j=0; j<sizeX[testCase]; j++){
                map[i][j][testCase] = tmp[j];
                if (map[i][j][testCase] >= '0' && map[i][j][testCase] <='9') sCnt++;
                else if (map[i][j][testCase] == 'A'){
                    startY = i; startX = j;
                    visited[i][j][testCase] = 1;
                }
            }
        }
        for(int i=0; i<sCnt; i++){
            Sig s;
            cin>>s.s>>s.d>>s.ew>>s.sn;
            sig[testCase][i] = s;
        }
        int ans = moving_truck(testCase, startY, startX);
        if (!ans) cout<<"impossible\n";
        else cout<<ans<<"\n";
        testCase++;
    }
}
