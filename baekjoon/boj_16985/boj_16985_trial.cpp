#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
using namespace std;
struct Point{
    int y, x, z;
};
vector<int> v;
int map[5][5][5], ans[5][5][5], visited[5][5][5], ans_min=9999, temp=0;
int rright[5][5][5], rrright[5][5][5], rrrright[5][5][5], move_x[6]={1,0,-1,0,0,0}, move_y[6]={0,1,0,-1,0,0}, move_z[6]={0,0,0,0,1,-1};
int num[4]={1,2,3,4}, select[5];
bool check_boundary(int y, int x, int z){
    if (y>=0 && y<5 && x>=0 && x<5 && z>=0 && z<5) return true;
    return false;
}
int find_shortest(){
    queue<Point> q;
    if (ans[0][0][0] || ans[4][4][4]) return 0;
    visited[0][0][0]=1;
    Point start;
    start.y=0; start.x=0; start.z=0;
    q.push(start);
    while(!q.empty()){
        Point temp=q.front(); q.pop();
        for(int d=0; d<6; d++){
            Point next;
            next.y=temp.y+move_y[d], next.x=temp.x+move_x[d], next.z=temp.z+move_z[d];
            if (check_boundary(next.y, next.x, next.z) && !visited[next.y][next.x][next.z] && !ans[next.y][next.x][next.z]){
                q.push(next);
                visited[next.y][next.x][next.z]=visited[temp.y][temp.x][temp.z]+1;
            }
        }
    }
    return visited[4][4][4];
}
void make_turn(){
    for(int z=0; z<5; z++){
        for(int y=0; y<5; y++){
            for(int x=0; x<5; x++){
                rright[y][x][z]=map[4-x][y][z];
            }
        }
        for(int y=0; y<5; y++){
            for(int x=0; x<5; x++){
                rrright[y][x][z]=rright[4-x][y][z];
            }
        }
        for(int y=0; y<5; y++){
            for(int x=0; x<5; x++){
                rrrright[y][x][z]=rrright[4-x][y][z];
            }
        }
    }
}
void dfs(int cnt){
    if(cnt == 5){
        for(int z=0; z<5; z++){
            for(int y=0; y<5; y++){
                for(int x=0; x<5; x++){
                    if (select[z]==4) ans[y][x][z]=map[y][x][v[z]-1];
                    else if (select[z]==1) ans[y][x][z]=rright[y][x][v[z]-1];
                    else if (select[z]==2) ans[y][x][z]=rrright[y][x][v[z]-1];
                    else if (select[z]==3) ans[y][x][z]=rrrright[y][x][v[z]-1];
                }
            }
        }
        temp=find_shortest();
        if (temp) ans_min=min(ans_min, temp);
    }   

    for(int i = 0; i < 5; i++){
        select[cnt] = num[i];
        dfs(cnt+1);
    }
}
int main(){
    for(int z=0; z<5; z++){
        for(int a=0; a<5; a++){
            for(int b=0; b<5; b++){
                cin>>map[a][b][z];
            }
        }
    }
    make_turn();
    for (int i = 0; i < 5; i++) {
		v.push_back(i+1);
	}
	do {
        memset(visited, 0, sizeof(visited));
        memset(ans, 0, sizeof(ans));
        dfs(0);
        temp=find_shortest();
  
	} while (next_permutation(v.begin(), v.end()));
    if (ans_min==9999) cout<<"-1";
    else cout<<ans_min-1;
}
