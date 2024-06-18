#include <iostream>
#include <queue>
using namespace std;
bool red=false, blue=false;
char map[10][10];
int visited[10][10][10][10], move_x[4]={1,0,-1,0}, move_y[4]={0,1,0,-1}, red_y=0, red_x=0, blue_y=0, blue_x=0, end_y=0, end_x=0, size_y=0, size_x=0;
string ans;
struct Pos{
    int rx, ry, bx, by, times;
    string dir;
};
queue<Pos> q;
bool which_one_first(int d, Pos temp){
    if (d==0 && temp.rx<temp.bx) return 0;
    else if (d==1 && temp.ry<temp.by) return 0;
    else if (d==2 && temp.rx>temp.bx) return 0;
    else if (d==3 && temp.ry>temp.by) return 0;
    return 1;
}
char add_dir(int d){
    if (d==0) return 'R';
    else if (d==1) return 'D';
    else if (d==2) return 'L';
    return 'U';
}
Pos moving_red_ball(int d, Pos temp){
    Pos next=temp;
    while(1){
        next.ry+=move_y[d];
        next.rx+=move_x[d];
        if ((map[next.ry][next.rx]=='#') || (next.ry==next.by && next.rx==next.bx)){
            next.ry-=move_y[d];
            next.rx-=move_x[d];
            return next;
        }
        else if (map[next.ry][next.rx]=='O'){
            next.ry=0;
            next.rx=0;
            red=true;
            return next;
        }
        else continue;
    }
    return next;
}
Pos moving_blue_ball(int d, Pos temp){
    Pos next=temp;
    while(1){
        next.by+=move_y[d];
        next.bx+=move_x[d];
        if ((map[next.by][next.bx]=='#') || (next.ry==next.by && next.rx==next.bx)){
            next.by-=move_y[d];
            next.bx-=move_x[d];
            return next;
        }
        else if (map[next.by][next.bx]=='O'){
            next.by=0;
            next.bx=0;
            blue=true;
            return next;
        }
        else continue;
    }
    return next;
}
int use_bfs(){
    while(!q.empty()){
        Pos temp=q.front(); Pos next; q.pop();
        if (temp.times>=10) break;
        for(int d=0; d<4; d++){
            bool check=which_one_first(d, temp);
            if (check) next=moving_blue_ball(d, moving_red_ball(d, temp));
            else next=moving_red_ball(d, moving_blue_ball(d, temp));
            if (red && !blue){
                ans=next.dir+add_dir(d);
                return next.times+1;
            }
            if ((next.ry==0 && next.rx==0) || (next.by==0 && next.bx==0)){
                red=false; blue=false;
                continue;
            }
            next.times++;
            next.dir+=add_dir(d);
            if (!visited[next.ry][next.rx][next.by][next.bx]){
                q.push(next);
                visited[next.ry][next.rx][next.by][next.bx]=1;
            }
        }
    }
    return -1;
}
int main(){
    Pos start;
    int num=0;
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
    start.rx=red_x; start.ry=red_y; start.by=blue_y; start.bx=blue_x; start.times=0, start.dir="";
    q.push(start);
    visited[start.ry][start.rx][start.by][start.bx]=1;
    num=use_bfs();
    if (num) cout<<num<<"\n"<<ans;
    else cout<<"-1";
}
