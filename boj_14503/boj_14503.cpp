#include <iostream>
using namespace std;
struct Info
{
    int x, y, dir;
};
Info start;
bool flag=false;
int map[50][50], visited[50][50], move_x[8]={0,1,0,-1,0,1,0,-1}, move_y[8]={-1,0,1,0,-1,0,1,0}, size_y=0, size_x=0, cnt=1;
void run_robot()
{
    Info temp, next;
    visited[start.y][start.x]=1;
    temp=start;
    while(!flag)
    {
        bool stop=false;
        for(int d=0; d<4; d++)
        {
            if(stop) break;
            next.y=temp.y+move_y[temp.dir+3-d];
            next.x=temp.x+move_x[temp.dir+3-d];
            if (next.y>=0 && next.y<size_y && next.x>=0 && next.x<size_x && visited[next.y][next.x]==0 && map[next.y][next.x]==0)
            {
                stop=true;
                next.dir=(temp.dir+3-d)%4;
                visited[next.y][next.x]=1;
                cnt++;
            }
            if (stop)
            temp=next;
        }
        if (!stop)
        {
            next.y=temp.y+move_y[(temp.dir+2)%4];
            next.x=temp.x+move_x[(temp.dir+2)%4];
            if (next.y>=0 && next.y<size_y && next.x>=0 && next.x<size_x)
            {
                if (map[next.y][next.x]==1)
                flag=true;
                else
                temp=next;
            }
        }
    }
    cout<<cnt;
}
int main()
{
    ios::sync_with_stdio(0);cin.tie(0); cout.tie(0);
    cin>>size_y>>size_x>>start.y>>start.x>>start.dir;
    for(int i=0; i<size_y; i++)
        for(int j=0; j<size_x; j++)
            cin>>map[i][j];
    run_robot();
}