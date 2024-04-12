#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct Person{
    int y, x;
    bool die;
};
Person people[30];
int size=0, people_cnt=0, trial=0, exitY=0, exitX=0, ans=0;
int dist[10][10], moveY[4]={0,1,0,-1}, moveX[4]={1,0,-1,0};
vector<vector<int> > maze(10, vector<int>(10, 0));
void print_people(){
    vector<vector<int> > temp_people(10, vector<int>(10, 0));
    for(int i=0; i<people_cnt; i++){
        if (people[i].die) continue;
        temp_people[people[i].y][people[i].x] = i + 1;
    }
    cout<<"people\n";
    for(int y=0; y<size; y++){
        for(int x=0; x<size; x++){
            cout<<temp_people[y][x]<<" ";
        }
        cout<<"\n";
    }
}
void print_maze(){
    cout<<"maze\n";
    for(int y=0; y<size; y++){
        for(int x=0; x<size; x++){
            cout<<maze[y][x]<<" ";
        }
        cout<<"\n";
    }
}
bool check_bound(int y, int x){
    return y>=0 && y<size && x>=0 && x<size;
}

bool close_distance(int y, int x, int ny, int nx){
    int now_distance = abs(exitY - y) + abs(exitX - x);
    int next_distance = abs(exitY - ny) + abs(exitX - nx);
    // cout<<"now: "<<now_distance<<" next: "<<next_distance<<"\n";
    return (now_distance > next_distance);
}

void move_person(){
    // cout<<"before move\n";
    // print_maze();
    // print_people();
    // cout<<"\n\n";
    for(int i=0; i<people_cnt; i++){
        if (people[i].die) {
            //cout<<i+1<<" is die";
            continue;
        }
        vector<int> close_dir;
        int y = people[i].y;
        int x = people[i].x;
        for(int d=0; d<4; d++){
            int ny = y + moveY[d];
            int nx = x + moveX[d];
            if (check_bound(ny, nx) && maze[ny][nx]<=0 && close_distance(y, x, ny, nx)){
                close_dir.push_back(d);
            }
        }
        //cout<<i+1<<" size: "<<close_dir.size()<<"\n";
        if (close_dir.size() > 1){
            for(int j=0; j<close_dir.size(); j++){
                //cout<<"direction: "<<close_dir[j]<<"\n";
                if (close_dir[j] == 1 || close_dir[j] == 3){
                    int ny = y + moveY[close_dir[j]];
                    int nx = x + moveX[close_dir[j]];
                    ans++;
                    if (maze[ny][nx] == -1){
                        //cout<<"????\n";
                        people[i].die = true;
                        break;
                    }
                    people[i].y = ny;
                    people[i].x = nx;
                    break;
                }
            }
        } else if (close_dir.size() == 1){
            // cout<<"direction: "<<close_dir[0]<<"\n";
            int ny = y + moveY[close_dir[0]];
            int nx = x + moveX[close_dir[0]];
            ans++;
            if (maze[ny][nx] == -1){
                people[i].die = true;
            }
            people[i].y = ny;
            people[i].x = nx;
        }
    }
    
}
void rotate_rigth90(){
    //cout<<"exit: "<<exitY<<" "<<exitX<<"\n";
    int startY = 0, startX=0, length = 0;
    bool stop = false;
    vector<vector<int> > temp_people(10, vector<int>(10, 0));
    for(int i=0; i<people_cnt; i++){
        if (people[i].die) continue;
        temp_people[people[i].y][people[i].x] = i + 1;
    }
    // 조건에 맞는 정사각형 찾기
    for(int len=1; len<=size; len++){
        if (stop) break;
        for(int sy=0; sy<size; sy++){
            if (stop) break;
            for(int sx=0; sx<size; sx++){
                if (stop) break;
                if (sx + len > size) continue;
                if (sy + len > size) continue;
                bool exit_flag=false, person_flag=false;
                for(int y=sy; y<sy+len; y++){
                    if (stop) break;
                    for(int x=sx; x<sx+len; x++){
                        if (!check_bound(y,x)) break;
                        if (maze[y][x] == -1) exit_flag = true;
                        if (temp_people[y][x] > 0) person_flag = true;
                        if (exit_flag && person_flag){
                            startY = sy;
                            startX = sx;
                            length = len;
                            stop = true;
                            break;
                        }
                    }
                }
            }
        }
    }
    //cout<<"rotate: "<<startY<<" "<<startX<<" "<<length<<"\n";
    // 오른쪽으로 90도 회전하기 + exit좌표 업데이트 필수 + 벽의 경우 -1 + 탈출구는 숫자 유지
    // maze랑 temp_people 모두 회전한 뒤, people 업데이트
    int next_people[10][10];
    memset(next_people, 0, sizeof(next_people));
    int next_maze[10][10];
    memset(next_maze, 0, sizeof(next_maze));
    for(int y=startY; y<startY+length; y++){
        for(int x=startX; x<startX+length; x++){
            //cout<<"to: "<<y<<" "<<x<<" from: "<<x+startY<<startY+length - 1 - y + startX<<"\n";
            next_people[x+startY-startX][startY+length - 1 - y + startX] = temp_people[y][x];
            //next_maze[x+startY][startY+length - 1 - y + startX] = maze[y][x];
            //if (next_maze[x][startY+length - 1 - y + startX] == 0) next_maze[x][startY+length - 1 - y + startX] = 0;
            if (maze[y][x] == 0) {
                next_maze[x+startY-startX][startY+length-1 -y + startX] = 0;
            }
            else if (maze[y][x] == -1) {
                next_maze[x+startY-startX][startY+length-1 -y + startX] = -1;
                // exitY = x;
                // exitX = startX+length-1 -y;
            }
            else {
                next_maze[x+startY-startX][startY+length-1 -y + startX] = maze[y][x] - 1;
            }

            // for(int y = startY; y < startY + length; y++) {
            //     for(int x = startX; x < startX + length; x++) {
            //         int rotatedY = x - startX + startY;
            //         int rotatedX = startY + length - 1 - (y - startY + startX);
                    
            //         next_people[rotatedY][rotatedX] = temp_people[y][x];

            //         if (maze[y][x] == 0) {
            //             next_maze[rotatedY][rotatedX] = 0;
            //         } else if (maze[y][x] == -1) {
            //             next_maze[rotatedY][rotatedX] = -1;
            //             // exitY = rotatedY;
            //             // exitX = rotatedX;
            //         } else {
            //             next_maze[rotatedY][rotatedX] = maze[y][x] - 1;
            //         }
            //     }
            // }
        }
    }
    // cout<<"next maze\n";
    // for(int y=0; y<size; y++){
    //     for(int x=0; x<size; x++){
    //         cout<<next_maze[y][x]<<" ";
    //     }
    //     cout<<"\n";
    // }
    for(int y=startY; y<startY+length; y++){
        for(int x=startX; x<startX+length; x++){
            maze[y][x] = next_maze[y][x];
            if (maze[y][x] == -1){
                exitY = y;
                exitX = x;
            }
        }
    }
    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            if (next_people[i][j] > 0){
                people[next_people[i][j] - 1].y = i;
                people[next_people[i][j] - 1].x = j;
            }
        }
    }
}
int main() {
    cin>>size>>people_cnt>>trial;
    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            cin>>maze[i][j];
        }
    }
    for(int i=0; i<people_cnt; i++){
        int y=0, x=0;
        cin>>y>>x;
        people[i].y = y-1;
        people[i].x = x-1;
        people[i].die = false;
    }
    cin>>exitY>>exitX;
    exitX-=1;
    exitY-=1;
    maze[exitY][exitX] = -1;
    
    for(int i=0; i<trial; i++){
        cout<<"\n\nturn: "<<i+1<<"\n";
        move_person();
        rotate_rigth90();
        // cout<<"after move: "<<i+1<<"\n";
        // cout<<"exit: "<<exitY<<" "<<exitX<<"\n";
        // print_people();
        // rotate_rigth90();
        // cout<<"after turn: "<<i+1<<"\n";
        // cout<<"exit: "<<exitY<<" "<<exitX<<"\n";
        // cout<<"over!!\n";
        // print_maze();
        // print_people();
        // for(int a=0; a<people_cnt; a++){
        //     cout<<a+1<<" person is die?"<<people[a].die<<"\n";
        // }   
    }
    cout<<ans<<"\n";
    cout<<exitY+1<<" "<<exitX+1;
    
    
    return 0;
}