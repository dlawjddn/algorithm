#include <iostream>
#include <queue>
#include <algorithm>
#include <cstring>

using namespace std;

struct AirCondition{
    int y, x, air;
};
struct Room{
    int y, x;
};
AirCondition ac[400];
Room work_room[400];
int map[20][20], visited[20][20], wall[20][20][4], cool[20][20], wind[20][20], moveY[4]={0,-1,0,1}, moveX[4]={-1,0,1,0};
int len = 0, wall_cnt = 0, hope = 0, ac_cnt=0, room_cnt=0;

bool checkBound(int y, int x){
    return y >=0 && y<len && x>=0 && x<len;
}
void make_wind(int sy, int sx, int d){
    int local_visited[20][20];
    memset(local_visited, 0, sizeof(local_visited));
    queue<pair<int, int> > q;

    q.push(make_pair(sy+moveY[d], sx+moveX[d]));
    local_visited[sy+moveY[d]][sx+moveX[d]] = 5;
    //cool[sy+moveY[d]][sx+moveX[d]] += 5;

    while(!q.empty()){
        int y = q.front().first;
        int x = q.front().second; q.pop();
        int d1 = d - 1;
        int d2 = d + 1;
        if (d1 < 0) d1 = 3;
        if (d2 > 3) d2 = 0;
        // 내 진행방향과 반대 방향으로 장애물을 확인해야함

        // - 자 방향
        int ny = y + moveY[d];
        int nx = x + moveX[d];

        if (!local_visited[ny][nx] && !wall[ny][nx][(d+2)%4] && checkBound(ny, nx)){
            //cool[ny][nx] += (local_visited[y][x] - 1);
            if (visited[y][x] != 2){
                q.push(make_pair(ny, nx));
                local_visited[ny][nx] = local_visited[y][x] - 1;
            }
        }

        int check_ny1 = y + moveY[d1];
        int check_nx1 = x + moveX[d1];
        int ny1 = check_ny1 + moveY[d];
        int nx1 = check_nx1 + moveX[d];

        if (!local_visited[ny1][nx1] && checkBound(check_ny1, check_nx1) && checkBound(ny1, nx1) &&!wall[check_ny1][check_nx1][(d1+2)%4] && !wall[ny1][nx1][(d+2)%4]){
            //cool[ny1][nx1] += (local_visited[y][x] - 1);
            if (visited[y][x] != 2){
                q.push(make_pair(ny1, nx1));
                local_visited[ny1][nx1] = local_visited[y][x] - 1;
            }
        }

        int check_ny2 = y + moveY[d2];
        int check_nx2 = x + moveX[d2];
        int ny2 = check_ny2 + moveY[d];
        int nx2 = check_nx2 + moveX[d];

        if (!local_visited[ny2][nx2] && checkBound(check_ny2, check_nx2) && checkBound(ny2, nx2) && !wall[check_ny2][check_nx2][(d2+2)%4] && !wall[ny2][nx2][(d+2)%4]){
            //cool[ny2][nx2] += (local_visited[y][x] - 1);
            if (visited[y][x] != 2){
                q.push(make_pair(ny2, nx2));
                local_visited[ny2][nx2] = local_visited[y][x] - 1;
            }
        }
    }
    for(int i=0; i<len; i++){
        for(int j=0; j<len; j++){
            wind[i][j]+=local_visited[i][j];
        }
    }
}
void windy(){
    for(int i=0; i<ac_cnt; i++){
        make_wind(ac[i].y, ac[i].x, ac[i].air - 2);
    }
}
void mix_and_minus(){
    int next_map[20][20];
    memset(next_map, 0, sizeof(next_map));
    for(int y=0; y<len; y++){
        for(int x=0; x<len; x++){
            int amount = 0;
            for(int d=0; d<4; d++){
                int ny = y + moveY[d];
                int nx = x + moveX[d];
                if (checkBound(ny, nx) && (cool[y][x] - cool[ny][nx]) >= 4 && !wall[y][x][d]){
                    int give = (cool[y][x] - cool[ny][nx]) / 4;
                    next_map[ny][nx] += give;
                    amount += give;
                }
            }
            next_map[y][x] += (cool[y][x] - amount);
        }
    }
    cout<<"섞은 뒤\n";
    for(int i=0; i<len; i++){
        for(int j=0; j<len; j++){
            cout<<next_map[i][j]<<" ";
        }
        cout<<"\n";
    }
    cout<<"\n";
    for(int i=0; i<len; i++){
        for(int j=0; j<len; j++){
            if ((i==0 || i == len - 1 || j ==0 || j == len - 1) && next_map[i][j] != 0){
                next_map[i][j]-=1;
            }
            cool[i][j] = next_map[i][j];
        }
    }
    // cout<<"가 빼고";
    // for(int i=0; i<size; i++){
    //     for(int j=0; j<size; j++){
    //         cout<<next_map[i][j]<<" ";
    //     }
    //     cout<<"\n";
    // }
}
bool check_cool(){
    for(int i=0; i<room_cnt; i++){
        int y = work_room[i].y;
        int x = work_room[i].x;
        if (cool[y][x] < hope) return false;
    }
    return true;
}
int main() {
    cin>>len>>wall_cnt>>hope;
    for(int i=0; i<len; i++){
        for(int j=0; j<len; j++){
            cin>>map[i][j];
            if (map[i][j] == 1){
                Room room;
                room.y = i;
                room.x = j;
                work_room[room_cnt++] = room;
            }
            if (map[i][j] >= 2 && map[i][j] <= 5){
                AirCondition air;
                air.y = i;
                air.x = j;
                air.air = map[i][j];
                ac[ac_cnt++] = air;
            }
        }
    }

    // 장애물 처리
    for(int i=0; i<wall_cnt; i++){
        int temp_y1=0, temp_x1=0, temp_dir1=0;
        int temp_y2=0, temp_x2=0, temp_dir2=0;
        cin>>temp_y1>>temp_x1>>temp_dir1;

        if (temp_dir1 == 0) temp_dir2 = 2;
        else if (temp_dir1 == 1) temp_dir2 = 3;
        else if (temp_dir1 == 2) temp_dir2 = 0;
        else temp_dir2 = 1;
        temp_y2 = (temp_y1-1) + moveY[temp_dir1];
        temp_x2 = (temp_x1-1) + moveX[temp_dir1];

        wall[temp_y1-1][temp_x1-1][temp_dir1] = 1;
        wall[temp_y2][temp_x2][temp_dir2] = 1;
    }
    // for(int z=0; z<4; z++){
    //     for(int y=0; y<len; y++){
    //         for(int x=0; x<len; x++){
    //             cout<<wall[y][x][z]<<" ";
    //         }
    //         cout<<"\n";
    //     }
    //     cout<<"\n";
    // }
    // cout<<"\n";
    windy();
    // for(int i=0; i<len; i++){
    //     for(int j=0; j<len; j++){
    //         cout<<wind[i][j]<<" ";
    //     }
    //     cout<<"\n";
    // }
    int ans = 0;
    while(1){
        ans++;
        cout<<ans<<"\n";
        if (ans > 100){
            cout<<"-1";
            break;
        }
        for(int i=0; i<len; i++){
            for(int j=0; j<len; j++){
                cool[i][j]+=wind[i][j];
            }
        }
        cout<<"바람\n";
        for(int i=0; i<len; i++){
            for(int j=0; j<len; j++){
                cout<<cool[i][j]<<" ";
            }
            cout<<"\n";
        }
        cout<<"\n";
        mix_and_minus();
        cout<<"뺀 뒤\n";
        for(int i=0; i<len; i++){
            for(int j=0; j<len; j++){
                cout<<cool[i][j]<<" ";
            }
            cout<<"\n";
        }
        cout<<"\n";
        if (check_cool()){
            cout<<ans;
            break;
        }
    }
    return 0;
}