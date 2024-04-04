#include <iostream>
#include <queue>
#include <algorithm>
#include <cstring>

using namespace std;

// 기준점 정하기는 문제에서 제시한 순서대로..
// 

struct Group{
    int y, x, normal, red;
};
struct Point{
    int y, x, color;
};
Group group[400];
int map[20][20], visited[20][20], moveX[4]={1,0,-1,0}, moveY[4]={0,1,0,-1}, size=0, limit = 0, ans = 0;

void bfs(int y, int x, int group_idx){
    group[group_idx].y = y;
    group[group_idx].x = x;
    group[group_idx].normal = 1;
    group[group_idx].red = 0;

    queue<Point> q;
    Point start;
    start.y = y;
    start.x = x;
    start.color = map[y][x];
    q.push(start);
    visited[y][x] = group_idx;
    while(!q.empty()){
        int y = q.front().y;
        int x = q.front().x; 
        int origin = q.front().color; q.pop();
        for(int d=0; d<4; d++){
            int ny = y + moveY[d];
            int nx = x + moveX[d];
            if (ny >=0 && ny < size && nx >=0 && nx < size && map[ny][nx] != -1){
                if (map[ny][nx] == 0){
                    if (visited[ny][nx] != group_idx){
                        Point next;
                        next.y = ny;
                        next.x = nx;
                        next.color = origin;
                        group[group_idx].red += 1;
                        q.push(next);
                        visited[ny][nx] = group_idx;
                    } 
                } else if (map[ny][nx] <= limit){
                    if (map[ny][nx] == origin && visited[ny][nx] == 0){
                        Point next;
                        next.y = ny;
                        next.x = nx;
                        next.color = origin;
                        group[group_idx].normal += 1;
                        q.push(next);
                        visited[ny][nx] = group_idx;
                    }
                }
            }
        }
    }

}
void delete_bomb(int y, int x, int color){
    map[y][x] = 9;
    visited[y][x] = 1;
    for(int d=0; d<4; d++){
        int ny = y + moveY[d];
        int nx = x + moveX[d];
        if (ny >= 0 && ny < size && nx >= 0 && nx < size){
            if (map[ny][nx] == color || map[ny][nx] == 0){
                delete_bomb(ny, nx, color);
            }
        }
    }
}
void gravity(){
    for(int x=0; x<size; x++){
        int down_cnt = 0;
        for(int y = size-1; y>=0; y--){
            if (map[y][x] == 9) down_cnt++;
            else if (map[y][x] == -1) down_cnt = 0;
            else {
                if (!down_cnt) continue;
                map[y+down_cnt][x] = map[y][x];
                map[y][x] = 9;
            }
        }
    }
}
void rotate_left90(){
    int temp_map[size][size];
    for(int y=0; y<size; y++){
        for(int x=0; x<size; x++){
            temp_map[y][x] = map[x][size - y - 1];
        }
    }
    memset(map, 0, sizeof(map));
    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            map[i][j] = temp_map[i][j];
        }
    }
}
int bomb(){
    memset(visited, 0, sizeof(visited));
    int group_idx = 0;
    // 그룹화 하기
    for(int i= size - 1; i >=0 ; i--){
        for(int j=0; j<size; j++){
            if (map[i][j] > 0  && map[i][j] <= limit && !visited[i][j]){
                bfs(i, j, ++group_idx);
            }
        }
    }
    int max_idx = -1, max_size=-1, min_red = 99;
    // 가장 큰 그룹 찾기
    // for(int i=0; i<size; i++){
    //     for(int j=0; j<size; j++){
    //         cout<<map[i][j]<<" ";
    //     }
    //     cout<<"\n";
    // }
    // cout<<"\n";
    for(int i=1; i<=group_idx; i++){
        int temp_size = group[i].normal + group[i].red;
        if (temp_size < 2) continue;
        if (temp_size >= max_size){
            if (temp_size > max_size){
                max_idx = i;
                max_size = temp_size;
                min_red = group[i].red;
            } else {
                if (min_red > group[i].red){
                    max_idx = i;
                    max_size = temp_size;
                    min_red = group[i].red;
                }
            }
        }
    }
    if (max_size == -1) {
        return -1;
    }
    ans += (max_size * max_size);
    // cout<<"y: "<<group[max_idx].y<<" x: "<<group[max_idx].x<<"\n";
    // cout<<"max_size: "<<max_size<<"\n";
    // cout<<"min_red: "<<min_red<<"\n";
    // cout<<"ans: "<<ans<<"\n";
    // cout<<"\n";
    // 터트리기
    memset(visited, 0, sizeof(visited));
    delete_bomb(group[max_idx].y, group[max_idx].x, map[group[max_idx].y][group[max_idx].x]);
    // for(int i=0; i<size; i++){
    //     for(int j=0; j<size; j++){
    //         cout<<map[i][j]<<" ";
    //     }
    //     cout<<"\n";
    // }
    // cout<<"\n";
    //중력으로 떨어트리기
    gravity();
    // for(int i=0; i<size; i++){
    //     for(int j=0; j<size; j++){
    //         cout<<map[i][j]<<" ";
    //     }
    //     cout<<"\n";
    // }
    // cout<<"\n";
    //90도 회전 오른쪽
    rotate_left90();
    //중력으로 떨어트리기
    gravity();
    return 0;
}
int main() {
    cin>>size>>limit;
    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            cin>>map[i][j];
        }
    }
    while(1) {
        int result = bomb();
        // for(int i=0; i<size; i++){
        //     for(int j=0; j<size; j++){
        //         cout<<map[i][j]<<" ";
        //     }
        //     cout<<"\n";
        // }
        // cout<<"ans: "<<ans<<"\n";
        // cout<<"\n";
        if (result == -1){
            cout<<ans;
            break;
        }
    }
    // 매 스테이지 마다 초기화 해줄거 있음 map, visited, group, group_idx
    // for(int i=1; i<=4; i++){
    //     cout<<"y: "<<group[i].y<<"\n";
    //     cout<<"x: "<<group[i].x<<"\n";
    //     cout<<"normal: "<<group[i].normal<<"\n";
    //     cout<<"red: "<<group[i].red<<"\n";
    //     cout<<"\n";
    // }
}