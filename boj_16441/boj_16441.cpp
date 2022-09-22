#include <iostream>
#include <queue>
using namespace std;
struct Point{
    int y, x, d;
};
queue<Point> q;
char map[100][100];
int visited[100][100][5], move_x[4]={1,0,-1,0}, move_y[4]={0,1,0,-1}, size_y=0, size_x=0;
void check_visited(){
    for(int y=0; y<size_y; y++){
        for(int x=0; x<size_x; x++){
            for(int d=0; d<4; d++){
                if (visited[y][x][d]){
                    visited[y][x][4]=1;
                    break;
                }
            }
        }
    }
}
void use_bfs(){
    while(!q.empty()){
        Point now=q.front(); q.pop();
        for(int d=0; d<4; d++){
            Point next;
            next.y=now.y+move_y[d], next.x=now.x+move_x[d], next.d=d;
            if (next.y>=0 && next.y<size_y && next.x>=0 && next.x<size_x && visited[next.y][next.x][next.d]==0 && map[next.y][next.x]!='#'){
                if (map[next.y][next.x]=='.'){
                    visited[next.y][next.x][next.d]=1;
                    q.push(next);
                }
                else if (map[next.y][next.x]=='+'){
                    int temp_y=next.y, temp_x=next.x;
                    visited[next.y][next.x][next.d]=1;
                    while(1){
                        temp_y+=move_y[d], temp_x+=move_x[d];
                        if (map[temp_y][temp_x]=='+') visited[temp_y][temp_x][d]=1;
                        else if (map[temp_y][temp_x]=='#'){
                            Point new_s;
                            new_s.y=temp_y-move_y[d], new_s.x=temp_x-move_x[d], new_s.d=d;
                            q.push(new_s);
                            break;
                        }
                        else{
                            Point new_s;
                            new_s.y=temp_y, new_s.x=temp_x, new_s.d=d;
                            visited[temp_y][temp_x][d]=1;
                            q.push(new_s);
                            break;
                        }
                    }
                }
            }
        }
    }
}
int main(){
    string s;
    cin>>size_y>>size_x;
    for(int i=0; i<size_y; i++){
        cin>>s;
        for(int j=0; j<size_x; j++){
            map[i][j]=s[j];
            if (map[i][j]=='W'){
                Point start;
                start.y=i, start.x=j, start.d=0;
                q.push(start);
                visited[start.y][start.x][start.d]=1;
            }
        }
    }
    use_bfs();
    check_visited();
    for(int a=0; a<size_y; a++){
        for(int b=0; b<size_x; b++){
            if (!visited[a][b][4] && map[a][b]=='.') cout<<"P";
            else cout<<map[a][b];
        }
        cout<<"\n";
    }
}