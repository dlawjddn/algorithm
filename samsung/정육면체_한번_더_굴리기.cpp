#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;
int moveN[7][4] = {
    {0,0,0,0},
    {3,2,4,5},
    {3,6,4,1},
    {6,2,1,5},
    {1,2,6,5},
    {1,4,6,3},
    {3,5,4,2}
};
int map[20][20], visited[20][20], group_size[400], moveY[4]={0,1,0,-1}, moveX[4]={1,0,-1,0};
int dice_bottom=0, dice_top=0, size=0, trial=0, score=0, dir=0, nowy=-1, nowx=-1;
void printMap(){
    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            cout<<visited[i][j]<<" ";
        }
        cout<<"\n";
    }
}

void dfs(int y, int x, int group_num, int cnt){
    visited[y][x] = group_num;
    group_size[group_num]++;
    for(int d=0; d<4; d++){
        int ny = y + moveY[d];
        int nx = x + moveX[d];
        if (ny >=0 && ny < size && nx >=0 && nx < size && map[ny][nx] == map[y][x] && visited[ny][nx] == 0){
            dfs(ny, nx, group_num, cnt + 1);
        }
    }
}
void grouping(){
    int group_cnt = 0;
    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            if (visited[i][j] == 0){
                dfs(i,j,++group_cnt, 1);
            }
        }
    }
    // cout<<"group_size\n";
    // for(int i=1; i<=group_cnt; i++){
    //     cout<<group_size[i]<<" ";
    // }
    // cout<<"\n";
}
void change_dir(int y, int x){
    //cout<<"now_dice_bottom: "<<dice_bottom<<"\n";
    if (map[y][x] > dice_bottom){
        dir--;
        if (dir < 0) dir = 3;
    } else if (map[y][x] < dice_bottom){
        dir++;
        if (dir > 3) dir = 0;
    }
    //cout<<"after_chnage: "<<dir<<"\n";
}
int main() {
    cin>>size>>trial;
    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            cin>>map[i][j];
        }
    }
    grouping();
    dice_bottom = 3;
    dice_top = 4;
    nowy = 0;
    nowx = 1;
    for(int i=0; i<trial; i++){
        // cout<<"dice_top: "<<dice_top<<" dice_bottom: "<<dice_bottom<<"\n";
        // cout<<"nowy: "<<nowy<<" nowx: "<<nowx<<" dir: "<<dir<<"\n";
        score += (group_size[visited[nowy][nowx]] * map[nowy][nowx]);
        // cout<<score<<"\n";
        // 다음 위치를 지정 & 방향을 지정
        change_dir(nowy, nowx);
        // 위치 조정 -> 바깥으로 넘어가는 경우에는 반사하도록 위치, 방향도 반대로
        int nexty = nowy + moveY[dir];
        int nextx = nowx + moveX[dir];
        if (nexty >= 0 && nexty < size && nextx >= 0 && nextx < size){
            dice_bottom = moveN[dice_top][dir];
            dice_top = 7 - dice_bottom;
            nowy = nexty;
            nowx = nextx;
        } else {
            if (dir == 0) dir = 2;
            else if (dir == 1) dir = 3;
            else if (dir == 2) dir = 0;
            else dir = 1;

            dice_bottom = moveN[dice_top][dir];
            dice_top = 7 - dice_bottom;
            nowy += moveY[dir];

            nowx += moveX[dir];
        }
        // dice_bottom 초기화해주기
    }
    cout<<score;
    return 0;
}