#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
struct Pos{
    int map[20][20], cnt;
};
int initial[20][20], move_y[4]={0,1,0,-1}, move_x[4]={1,0,-1,0}, length=0, ans=0;
queue<Pos> q;
Pos fusing_block(int d, Pos a){
    int visited[20][20];
    memset(visited, 0, sizeof(visited));
    if (d==0){
        for(int y=0; y<length; y++){
            int check=length-1;
            for(int x=length-2; x>=0; x--){
                if (!a.map[y][x]) continue;
                else{
                    if (a.map[y][check]==a.map[y][x] && !visited[y][check]){
                        a.map[y][check]=a.map[y][check]+a.map[y][x];
                        ans=max(ans, a.map[y][check]);
                        a.map[y][x]=0;
                        visited[y][check]=1;
                        check--;
                    }
                    else if ((a.map[y][check]==a.map[y][x] && visited[y][check])){
                        a.map[y][check]=a.map[y][check]+a.map[y][x];
                        a.map[y][x]=0;
                        check--;
                    }
                    else if ((a.map[y][check]!=a.map[y][x])){
                        if (!a.map[y][check]){
                            a.map[y][check]=a.map[y][check]+a.map[y][x];
                            a.map[y][x]=0;
                        }
                        else{
                            check--;
                            if (check==x)
                            continue;
                            a.map[y][check]=a.map[y][check]+a.map[y][x];
                            a.map[y][x]=0;
                        }
                    }
                }
            }
        }
    }
    else if (d==1){
        for(int x=0; x<length; x++){
            int check=length-1;
            for(int y=length-2; y>=0; y--){
                if (!a.map[y][x]) continue;
                else{
                    if (a.map[check][x]==a.map[y][x] && !visited[check][x]){
                        a.map[check][x]=a.map[check][x]+a.map[y][x];
                        ans=max(ans, a.map[check][x]);
                        a.map[y][x]=0;
                        visited[check][x]=1;
                        check--;
                    }
                    else if (a.map[check][x]==a.map[y][x] && visited[check][x]){
                        a.map[check][x]=a.map[check][x]+a.map[y][x];
                        a.map[y][x]=0;
                        check--;
                    }
                    else if (a.map[check][x]!=a.map[y][x]){
                        if (!a.map[check][x]){
                            a.map[check][x]=a.map[check][x]+a.map[y][x];
                            a.map[y][x]=0;
                        }
                        else{
                            check--;
                            if (check==y)
                            continue;
                            a.map[check][x]=a.map[check][x]+a.map[y][x];
                            a.map[y][x]=0;
                        }
                    }
                }
            }
        }
    }
    else if (d==2){
        for(int y=0; y<length; y++){
            int check=0;
            for(int x=1; x<length; x++){
                if (!a.map[y][x]) continue;
                else{
                    if (a.map[y][check]==a.map[y][x] && !visited[y][check]){
                        a.map[y][check]=a.map[y][check]+a.map[y][x];
                        ans=max(ans, a.map[y][check]);
                        a.map[y][x]=0;
                        visited[y][check]=1;
                        check++;
                    }
                    else if ((a.map[y][check]==a.map[y][x] && visited[y][check])){
                        a.map[y][check]=a.map[y][check]+a.map[y][x];
                        a.map[y][x]=0;
                        check++;
                    }
                    else if ((a.map[y][check]!=a.map[y][x])){
                        if (!a.map[y][check]){
                            a.map[y][check]=a.map[y][check]+a.map[y][x];
                            a.map[y][x]=0;
                        }
                        else{
                            check++;
                            if (check==x)
                            continue;
                            a.map[y][check]=a.map[y][check]+a.map[y][x];
                            a.map[y][x]=0;
                        }
                    }
                }
            }
        }
    }
    else{
        for(int x=0; x<length; x++){
            int check=0;
            for(int y=1; y<length; y++){
                if (!a.map[y][x]) continue;
                else{
                    if (a.map[check][x]==a.map[y][x] && !visited[check][x]){
                        a.map[check][x]=a.map[check][x]+a.map[y][x];
                        ans=max(ans, a.map[check][x]);
                        a.map[y][x]=0;
                        visited[check][x]=1;
                        check++;
                    }
                    else if (a.map[check][x]==a.map[y][x] && visited[check][x]){
                        a.map[check][x]=a.map[check][x]+a.map[y][x];
                        a.map[y][x]=0;
                        check++;
                    }
                    else if (a.map[check][x]!=a.map[y][x]){
                        if (!a.map[check][x]){
                            a.map[check][x]=a.map[check][x]+a.map[y][x];
                            a.map[y][x]=0;
                        }
                        else{
                            check++;
                            if (check==y)
                            continue;
                            a.map[check][x]=a.map[check][x]+a.map[y][x];
                            a.map[y][x]=0;
                        }
                    }
                }
            }
        }
    }
    a.cnt++;
    return a;
}
void use_bfs(){
    while(!q.empty()){
        Pos temp=q.front(); q.pop();
        for(int d=0; d<4; d++){
            Pos next = fusing_block(d, temp);
            if (next.cnt<5) q.push(next); 
        }
    }
    cout<<ans;
}
int main(){
    Pos start;
    cin>>length;
    for(int y=0; y<length; y++){
        for(int x=0; x<length; x++){
            cin>>initial[y][x];
            ans=max(ans, initial[y][x]);
        }
    }
    copy(&initial[0][0], &initial[0][0]+20*20, &start.map[0][0]);
    start.cnt=0;
    fusing_block(2, start);
    q.push(start);
    use_bfs();
}