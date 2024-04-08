#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;
struct Point{
    int y, x, dir;
};
queue<Point> monster;
queue<Point> egg;
int monster_cnt[5][5][26], map[5][5][30], moveY[8]={-1,-1,0,1,1,1,0,-1}, moveX[8]={0,-1,-1,-1,0,1,1,1};
int cnt=0, trial=0, packmanY=0, packmanX=0, ans=0;
bool check_bound(int y, int x){
    return y>=1 && y<=4 && x>=1 && x<=4;

}
void copy_monster(int t){
    int now_cnt = monster.size();
    for(int i=0; i<now_cnt; i++){
        Point temp_monster = monster.front(); monster.pop();
        monster.push(temp_monster);
        egg.push(temp_monster);
        //monster_cnt[temp_monster.y][temp_monster.x][t+2]++;
    }
    
}
void move_monster(int t){
    int limit = monster.size();
    for(int i=0; i<limit; i++){
        Point now = monster.front(); monster.pop();
        int start_dir = now.dir - 1;
        for(int d=0; d<8; d++){
            Point next;
            next.dir = start_dir + d;
            if (next.dir > 7) next.dir-=8;
            next.y = now.y + moveY[next.dir];
            next.x = now.x + moveX[next.dir];
            if (check_bound(next.y, next.x) && map[next.y][next.x][t] == 0 && !(next.y == packmanY && next.x == packmanX)){
                next.dir += 1;
                monster.push(next);
                monster_cnt[next.y][next.x][t+1]++;
                break;
            }
        }
    }
}
void move_packman(int tr){
    int first_d = 0, second_d = 0, third_d = 0, eat = 0;
    // 우선순위부터 상상상, 상상좌 ... 먼저 나온 놈이 우선순위 높음
    for(int f = 0; f<8; f+=2){
        int first_y = packmanY + moveY[f];
        int first_x = packmanX + moveX[f];
        if (!check_bound(first_y, first_x)) continue;
        for(int s = 0; s<8; s+= 2){
            int second_y = first_y + moveY[s];
            int second_x = first_x + moveX[s];
            if (!check_bound(second_y, second_x) || (first_y == second_y && first_x == second_x)) continue;
            for(int t=0; t<8; t+=2){
                int third_y = second_y + moveY[t];
                int third_x = second_x + moveX[t];
                if (!check_bound(third_y, third_x) || ((first_y == third_y && first_x == third_x) || (second_y == third_y && second_x == third_x))) continue;
                int temp_eat = monster_cnt[first_y][first_x][tr+1] + monster_cnt[second_y][second_x][tr+1] + monster_cnt[third_y][third_x][tr+1];
                if (temp_eat > eat){
                    eat = temp_eat;
                    first_d = f;
                    second_d = s;
                    third_d = t;
                }
            }
        }
    }
    int fy = packmanY + moveY[first_d];
    int fx = packmanX + moveX[first_d];
    cout<<"first: "<<fy<<" "<<fx<<"\n";
    if (monster_cnt[fy][fx][tr+1] != 0){
        monster_cnt[fy][fx][tr+1] = 0;
        for(int i=1; i<=2; i++){
            map[fy][fx][tr+1+i] = 1;
        }
    }
    int sy = fy + moveY[second_d];
    int sx = fx + moveX[second_d];
    cout<<"second: "<<sy<<" "<<sx<<"\n";
    if (monster_cnt[sy][sx][tr+1] != 0){
        monster_cnt[sy][sx][tr+1] = 0;
        for(int i=1; i<=2; i++){
            map[sy][sx][tr+1+i] = 1;
        }
    }
    int ty = sy + moveY[third_d];
    int tx = sx + moveX[third_d];
    cout<<"thrid: "<<ty<<" "<<tx<<"\n";
    if (monster_cnt[ty][tx][tr+1] != 0){
        monster_cnt[ty][tx][tr+1] = 0;
        for(int i=1; i<=2; i++){
            map[ty][tx][tr+1+i] = 1;
        }
    }
    int limit = monster.size();
    for(int i=0; i<limit; i++){
        Point temp = monster.front(); monster.pop();
        if (temp.y == fy && temp.x == fx) continue;
        if (temp.y == sy && temp.x == sx) continue;
        if (temp.y == ty && temp.x == tx) continue;
        monster.push(temp);
    }
    packmanY = ty;
    packmanX = tx;
}
void add_monster(int t){
    while(!egg.empty()){
        Point mon = egg.front(); egg.pop();
        monster.push(mon);
        monster_cnt[mon.y][mon.x][t+1]++;
    }
}
int main() {
    cin>>cnt>>trial>>packmanY>>packmanX;
    //map[packmanY][packmanX][0] = 1;
    for(int i=0; i<cnt; i++){
        Point temp;
        cin>>temp.y>>temp.x>>temp.dir;
        monster_cnt[temp.y][temp.x][0]++;
        monster.push(temp);
    }
    for(int i=0; i<trial; i++){
        cout<<"trial: "<<i+1<<"\n";
        cout<<"monster size: "<<monster.size()<<"\n";
        copy_monster(i);
        move_monster(i);
        cout<<"move_monster\n";
        cout<<"monster size: "<<monster.size()<<"\n";
        for(int a=1; a<=4; a++){
            for(int b=1; b<=4; b++){
                cout<<monster_cnt[a][b][i+1];
            }
            cout<<"\n";
        }
        cout<<"\n";
        cout<<"packman position: "<<packmanY<<" "<<packmanX<<"\n";
        move_packman(i);
        cout<<"move_packman\n";
        for(int a=1; a<=4; a++){
            for(int b=1; b<=4; b++){
                cout<<monster_cnt[a][b][i+1];
            }
            cout<<"\n";
        }
        cout<<"\n";
        add_monster(i);
        cout<<"add_monster\n";
        for(int a=1; a<=4; a++){
            for(int b=1; b<=4; b++){
                cout<<monster_cnt[a][b][i+1];
            }
            cout<<"\n";
        }
        cout<<"\n";
    }
    for(int i=1; i<=4; i++){
        for(int j=1; j<=4; j++){
            ans+=monster_cnt[i][j][trial];
        }
    }
    cout<<ans<<"\n";
    // for(int z=0; z<=trial; z++){
    //     cout<<"trial: "<<z<<"\n";
    //     for(int y=1; y<=4; y++){
    //         for(int x=1; x<=4; x++){
    //             cout<<monster_cnt[y][x][z]<<" ";
    //         }
    //         cout<<"\n";
    //     }
    //     cout<<"\n\n";
    // }
    
}