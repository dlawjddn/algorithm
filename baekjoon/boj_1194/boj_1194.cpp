#include <iostream>
#include <cstring>
#include <queue>
using namespace std;
struct Point{
    int y, x, z, cnt;
    bool key[6];
};
queue<Point> q;
char map[51][51];
int visited[51][51][64], move_y[4]={0,1,0,-1}, move_x[4]={1,0,-1,0}, size_y=0, size_x=0;
int check_keynum(char c, int now){
    int check=0;
    if (c=='a') check=1;
    else if (c=='b') check=2;
    else if (c=='c') check=4;
    else if (c=='d') check=8;
    else if (c=='e') check=16;
    else if (c=='f') check=32;
    return now+check;
}
int use_bfs(){
    while(!q.empty()){
        Point temp=q.front(); q.pop();
        for(int d=0; d<4; d++){
            Point next=temp;
            next.y+=move_y[d];
            next.x+=move_x[d];
            copy(temp.key, temp.key+6, next.key);
            if (next.y>=0 && next.y<size_y && next.x>=0 && next.x<size_x && next.z>=0 && next.z<64 && !visited[next.y][next.x][next.z]){
                if (map[next.y][next.x]=='1') return next.cnt+1;
                else if (map[next.y][next.x]>='a' && map[next.y][next.x]<='f'){
                    if (!next.key[map[next.y][next.x]-'a']){
                        next.z=check_keynum(map[next.y][next.x], next.z);
                        next.cnt++;
                        next.key[map[next.y][next.x]-'a']=next.cnt;
                        q.push(next);
                    }
                    else{
                        next.cnt++;
                        visited[next.y][next.x][next.z]=next.cnt;
                        q.push(next);
                    }
                }
                else if (map[next.y][next.x]>='A' && map[next.y][next.x]<='F'){
                    if (next.key[map[next.y][next.x]-'A']){
                        next.cnt++;
                        visited[next.y][next.x][next.z]=next.cnt;
                        q.push(next);
                    }
                }
                else if (map[next.y][next.x]=='.' || map[next.y][next.x]=='0'){
                    next.cnt++;
                    visited[next.y][next.x][next.z]=next.cnt;
                    q.push(next);
                }
            }
        }
    }
    return -1;
}
int main(){
    Point start;
    cin>>size_y>>size_x;
    for(int i=0; i<size_y; i++){
        string str;
        cin>>str;
        for(int j=0; j<size_x; j++){
            map[i][j]=str[j];
            if (map[i][j]=='0'){
                start.y=i; start.x=j; start.z=0, start.cnt=0;
                memset(start.key, 0, sizeof(start.key));
            }
        }
    }
    q.push(start);
    cout<<use_bfs();
}