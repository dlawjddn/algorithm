#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

// 시작점 0으로 만들어주기, 못 가는 곳 0이라고 체크하고 넘기지 않기
// -> 결국 좀 더 꼼꼼하면 맞추는 문제...
struct Shark{
    int y, x, level, eaten;
    
    Shark(int y, int x, int level, int eaten) : y(y), x(x), level(level), eaten(eaten) {}
};
int map[20][20], visited[20][20], moveX[4]={1,0,-1,0}, moveY[4]={0,1,0,-1}, len=0;

void printMap(){
    for(int i=0; i<len; i++){
        for(int j=0; j<len; j++){
            cout<<visited[i][j]<<" ";
        }
        cout<<"\n";
    }
    cout<<"\n";
}
pair<Shark, int> find_eating_fish(Shark shark){
    int min_dis = 9999;
    int ny = 0;
    int nx = 0;
    for(int i=0; i<len; i++){
        for(int j=0; j<len; j++){
            // 0이 아니면서 자기 레벨보다 낮은 물고기 중 가장 가까운
            if (map[i][j] != 0 && visited[i][j] != 0 && map[i][j] < shark.level && min_dis > visited[i][j]){
                ny = i;
                nx = j;
                min_dis = visited[i][j];
            }
        }
    }
    if (min_dis == 9999){
        return make_pair(shark, -1);
    } else { 
        map[ny][nx] = 0;
        int level = shark.level;
        int eaten = shark.eaten;
        if (shark.level - 1 == shark.eaten){
            level += 1;
            eaten = 0;    
        }
        else eaten += 1;
        return make_pair(Shark(ny, nx, level, eaten), min_dis);
    }
}

void cal_distance(Shark shark){
    queue<Shark> q;
    q.push(shark);
    visited[shark.y][shark.x] = 1;
    while(!q.empty()){
        Shark now = q.front(); q.pop();
        for(int d=0; d<4; d++){
            int ny = now.y + moveY[d];
            int nx = now.x + moveX[d];
            int level = now.level;
            if (ny >= 0 && ny< len && nx >= 0 && nx < len && map[ny][nx] <= level && visited[ny][nx] == 0){
                q.push(Shark(ny, nx, level, now.eaten));
                visited[ny][nx] = visited[now.y][now.x] + 1;
            }
        }
    }

}
int main(){
    int startY, startX;
    cin>>len;
    for(int i=0; i<len; i++){
        for(int j=0; j<len; j++){
            cin>>map[i][j];
            if (map[i][j] == 9){
                startY = i;
                startX = j;
                map[i][j] = 0;
            }
        }
    }
    int total_time = 0;
    Shark shark = Shark(startY, startX, 2, 0);
    while(1){
        cal_distance(shark);
        //printMap();
        pair<Shark, int> next = find_eating_fish(shark);        
        Shark next_shark = next.first;
        int min_time= next.second;
        if (min_time == -1){
            cout<< total_time;
            break;
        }
        total_time += min_time - 1;
        shark = next_shark;
        memset(visited, 0, sizeof(visited));
    }
}