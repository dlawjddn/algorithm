#include<iostream>
#include<queue>
using namespace std;
int map[52][52], moveX[4]={1,0,-1,0}, moveY[4]={0,1,0,-1}, cnt=0, sizeX=0, sizeY=0, limit=0;
bool checkBound(int y, int x){
    if (y>=0 && y<=sizeY+1 && x>=0 && x<=sizeX+1) return true;
    return false;
}
void bfs(int h) {
    queue<pair<int, int> > q;
    map[0][0] = h;
    q.push(make_pair(0,0));
    while (!q.empty()) {
        int y = q.front().first;
        int x = q.front().second; q.pop();
        for (int i = 0; i < 4; i++) {
            int ny = y + moveY[i];
            int nx = x + moveX[i];
            if (checkBound(ny, nx) && map[ny][nx] < h) {
                map[ny][nx] = h;
                q.push(make_pair(ny, nx));
            }
        }
    }
}
int main() {
    cin>>sizeY>>sizeX;
    for(int y=1; y<=sizeY; y++){
        string str;
        cin>>str;
        for(int x=1; x<=sizeX; x++){
            map[y][x]=str[x-1];
            if (limit<map[y][x]) limit=map[y][x];
        }
    }
    for(int h=1; h<=limit; h++){
        bfs(h);
        for(int y=1; y<=sizeY; y++){
            for(int x=1; x<=sizeX; x++){
                if (map[y][x]<h){
                    cnt++;
                    map[y][x]+=1;
                }
            }
        }
    }
    cout<<cnt;
}
