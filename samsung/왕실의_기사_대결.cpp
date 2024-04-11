#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
int size=0, knight_cnt=0, order_cnt=0;
int map[40][40], knight[40][40], knight_health[31], start_health[31];
int moveY[4]={-1, 0, 1, 0}, moveX[4]={0,1,0,-1};
bool move_with[31], knight_move[31];
void print_knight(){
    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            cout<<knight[i][j]<<" ";
        }
        cout<<"\n";
    }
}
void print_health(){
    for(int i=1; i<=knight_cnt; i++) cout<<knight_health[i]<<" ";
    cout<<"\n";
}
bool check_bound(int y, int x){
    return y>=0 && y<size && x>=0 && x<size;
}
bool can_move(int sy, int sx, int dir){
    int y = sy;
    int x = sx;
    while(1){
        int ny = y + moveY[dir];
        int nx = x + moveX[dir];
        if (!check_bound(ny,nx)) return false;
        if (map[ny][nx] == 2) return false;
        else {
            if (knight[ny][nx] == 0) return true;
        }
        y = ny;
        x = nx;
    }
}
bool check_together(int num, int d){
    bool new_knight[31];
    memset(new_knight, 0, sizeof(new_knight));
    for(int y=0; y<size; y++){
        for(int x=0; x<size; x++){
            if (knight[y][x] == num){
                int sy = y;
                int sx = x;
                while(1){
                    int ny = sy + moveY[d];
                    int nx = sx + moveX[d];
                    if (!check_bound(ny,nx)) break;
                    if (map[ny][nx]!=2 && knight[ny][nx] == 0) break;
                    if (knight[ny][nx] > 0){
                        if (!knight_move[knight[ny][nx]]) {
                            return false;
                        }
                        else {
                            if (knight[ny][nx] != num)
                                new_knight[knight[ny][nx]] = true;
                            move_with[knight[ny][nx]] = true;
                        }
                    }
                    sy = ny;
                    sx = nx;
                }
            }
        }
    }
    // cout<<"size!!!\n";
    // for(int i=1; i<=knight_cnt; i++){
    //     cout<<new_knight[i]<<" ";
    // }
    // cout<<"\n";
    for(int i=1; i<=knight_cnt; i++){
        if (new_knight[i]){
            if (!check_together(i, d)) return false;
        }
    }
    return true;
}
bool move_knight(int knight_num, int d){
    int temp_knight[40][40], visited[40][40];
    memset(knight_move, 1, sizeof(knight_move));
    memset(temp_knight, 0, sizeof(temp_knight));
    memset(visited, 0, sizeof(visited));
    memset(move_with, 0, sizeof(move_with));
    // 각 기사들이 해당 방향으로 진행 가능한지 파악
    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            if (knight[i][j] > 0){
                if (!can_move(i,j,d)){
                    knight_move[knight[i][j]] = false;
                }
            }
        }
    }
    // 명령을 내린 기사가 못 움직이는 경우
    if (!knight_move[knight_num]) return false ;

    if (!check_together(knight_num, d)) return false;
    move_with[knight_num] =true;
    // for(int y=0; y<size; y++){
    //     for(int x=0; x<size; x++){
    //         if (knight[y][x] == knight_num){
    //             int sy = y;
    //             int sx = x;
    //             while(1){
    //                 int ny = sy + moveY[d];
    //                 int nx = sx + moveX[d];
    //                 if (!check_bound(ny,nx)) break;
    //                 if (map[ny][nx]!=2 && knight[ny][nx] == 0) break;
    //                 if (knight[ny][nx] > 0){
    //                     if (!knight_move[knight[ny][nx]]) return false;
    //                     else move_with[knight[ny][nx]] = true;
    //                 }
    //                 sy = ny;
    //                 sx = nx;
    //             }
    //         }
    //     }
    // }
    // 이제 움직일 차례
    for(int y=0; y<size; y++){
        for(int x=0; x<size; x++){
            if (knight[y][x] > 0){
                if (move_with[knight[y][x]])
                temp_knight[y + moveY[d]][x + moveX[d]] = knight[y][x];
                else
                temp_knight[y][x] = knight[y][x];
            }
        }
    }
    for(int y=0; y<size; y++){
        for(int x=0; x<size; x++){
            knight[y][x] = temp_knight[y][x];
        }
    }
    return true;
}
void fight_damage(int me){
    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            if (knight[i][j] == me) continue;
            if (move_with[knight[i][j]] && map[i][j] == 1) knight_health[knight[i][j]]--;
        }
    }
}
void delete_knight(int num){
    for(int y=0; y<size; y++){
        for(int x=0; x<size; x++){
            if (knight[y][x] == num)
            knight[y][x] = 0;
        }
    }
}
int main() {
    cin>>size>>knight_cnt>>order_cnt;
    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            cin>>map[i][j];
        }
    }
    for(int i=0; i<knight_cnt; i++){
        int startY=0, startX=0, sizeY=0, sizeX=0, hp=0;
        cin>>startY>>startX>>sizeY>>sizeX>>hp;
        knight_health[i+1] = hp;
        start_health[i+1] = hp;
        int cnt = 0;
        for(int y=startY; y<=sizeY+startY-1; y++){
            for(int x=startX; x<=sizeX+startX-1; x++){
                knight[y-1][x-1] = i + 1;
            }
        }
    }
    cout<<"\n";
    print_knight();
    for(int i=0; i<order_cnt; i++){
        int order_num=0, order_dir=0;
        cin>>order_num>>order_dir;
        if (knight_health[order_num] <= 0) continue;
        if (move_knight(order_num, order_dir)){
            cout<<"move!\n";
            fight_damage(order_num);
        }
        for(int i=1; i<=knight_cnt; i++){
            if(knight_health[i] <= 0) {
                knight_health[i] = 0;
                delete_knight(i);
            }
        }
        cout<<"order: "<<order_num<<" "<<order_dir<<"\n";
        cout<<"turn: "<<i+1<<"\n";
        cout<<"after turn :"<<i+1<<"\n";
        print_knight();
        cout<<"\n";
        print_health();
        cout<<"\n";
    }
    int ans = 0;
    for(int i=1; i<=knight_cnt; i++){
        // cout<<knight_health[i]<<" ";
        if (knight_health[i] != 0){
            ans += (start_health[i] - knight_health[i]);
        }
    }
    cout<<ans;
    
    return 0;
}