#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;
char map[10][10];
bool red=false, blue=false;
int move_x[4]={1,0,-1,0}, move_y[4]={0,1,0,-1}, size_y=0, size_x=0, red_x=0, red_y=0, blue_x=0, blue_y=0, end_y=0, end_x=0;
struct Pos{
    int rx, ry, by, bx, times;
};
queue<Pos> q;
bool which_one_first(int d, Pos temp){ // true-red
    if (d==0 && temp.rx < temp.bx) return false;
    else if (d==1 && temp.ry < temp.by) return false;
    else if (d==2 && temp.rx > temp.bx) return false;
    else if (d==3 && temp.ry > temp.by) return false;
    return true; 
}
Pos moving_red_ball(int d, Pos temp){
    Pos next=temp;
    while(1){
        next.rx+=move_x[d];
        next.ry+=move_y[d];
        if (next.rx>=0 && next.rx<size_x && next.ry>=0 && next.ry<size_y){
            if (map[next.ry][next.rx]=='#' || (next.ry==next.by && next.rx==next.bx)){
                next.ry-=move_y[d];
                next.rx-=move_x[d];
                break;
            }
            else if (map[next.ry][next.rx]=='O'){
                next.ry=0;
                next.rx=0;
                red=true;
                break;
            }
            else if (map[next.ry][next.rx]=='.') continue;
        }
        else break;
    }
    return next;
}
Pos moving_blue_ball(int d, Pos temp){
    Pos next=temp;
    while(1){
        next.bx+=move_x[d];
        next.by+=move_y[d];
        if (next.bx>=0 && next.bx<size_x && next.by>=0 && next.by<size_y){
            if (map[next.by][next.bx]=='#' || (next.ry==next.by && next.rx==next.bx)){
                next.by-=move_y[d];
                next.bx-=move_x[d];
                break;
            }
            else if (map[next.by][next.bx]=='O'){
                next.by=0;
                next.bx=0;
                blue=true;
                break;
            }
            else if (map[next.by][next.bx]=='.') continue;
        }
        else break;
    }
    return next;
}
int use_bfs(){
    while(!q.empty()){
        Pos temp=q.front(); q.pop();
        if (temp.times>=10) break;
        for(int d=0; d<4; d++){
            bool check = which_one_first(d, temp);
            Pos next;
            if (check) next=moving_blue_ball(d, moving_red_ball(d, temp));
            else next=moving_red_ball(d, moving_blue_ball(d, temp));
            if (red==true && blue==false) return 1;
            next.times++;
            if ((next.ry==0 && next.rx==0) || (next.bx==0 && next.by==0)){
                red=false, blue=false;
                continue;
            }
            q.push(next);
        }
    }
    return 0;
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    Pos start;
    cin>>size_y>>size_x;
    for(int i=0; i<size_y; i++){
        string str;
        cin>>str;
        for(int j=0; j<size_x; j++){
            map[i][j]=str[j];
            if (map[i][j]=='R'){
                red_y=i, red_x=j;
            }
            else if (map[i][j]=='B'){
                blue_y=i, blue_x=j;
            }
            else if (map[i][j]=='O'){
                end_y=i, end_x=j;
            }
        }
    }
    start.ry=red_y, start.rx=red_x, start.by=blue_y, start.bx=blue_x, start.times=0;
    q.push(start);
    cout<<use_bfs();
}