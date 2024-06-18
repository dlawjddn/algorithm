#include <iostream>
#include <queue>
#include <cmath>
#include <cstring>
using namespace std;
struct Point
{
    int y, x;
};
Point virus[10];
int map[50][50], temp_map[50][50], visited[50][50], arr[10], move_x[4]={1,0,-1,0}, move_y[4]={0,1,0,-1}, size_sq=0, max_virus=0, cnt_empty=0, cnt_virus=0, ans=987654321;
void spread_virus()
{
    queue<Point> q;
    Point temp, next;
    int temp_cnt=0, temp_max=1;
    for(int a=0; a<max_virus; a++)
    {
        q.push(virus[arr[a]]);
        visited[virus[arr[a]].y][virus[arr[a]].x]=1;
    }
    while(!q.empty())
    { 
        temp=q.front(); q.pop();
        for(int d=0; d<4; d++)
        {
            next.y=temp.y+move_y[d], next.x=temp.x+move_x[d];
            if (next.y>=0 && next.y<size_sq && next.x>=0 && next.x<size_sq && visited[next.y][next.x]==0 && map[next.y][next.x]==0)
            {
                visited[next.y][next.x]=visited[temp.y][temp.x]+1;
                temp_max=max(temp_max, visited[next.y][next.x]);
                q.push(next);
                temp_cnt++;
                if (temp_cnt==cnt_empty-max_virus)
                ans=min(ans, visited[next.y][next.x]);
            }
        }
    }
    if (temp_cnt==cnt_empty-max_virus)
    ans=min(ans, temp_max);
}
void find_out(int idx, int num)
{
    if (idx==max_virus-1)
    {
        memset(visited, 0, sizeof(visited));
        spread_virus();
        return ;
    }
    else
    {
        idx++;
        for(int b=num+1; b<cnt_virus; b++)
        {
            arr[idx]=b;
            find_out(idx, b);
        }
    }
}
void combination()
{
    for(int a=0; a<cnt_virus; a++)
    {
        int idx=0;
        arr[idx]=a;
        find_out(idx, a);
    }
    if (ans==987654321)
    cout<<"-1";
    else
    cout<<ans-1;
}
int main()
{
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>size_sq>>max_virus;
    for(int i=0; i<size_sq; i++)
    {
        for(int j=0; j<size_sq; j++)
        {
            cin>>map[i][j];
            if (map[i][j]==0)
            cnt_empty++;
            else if (map[i][j]==2)
            {
                cnt_empty++;
                virus[cnt_virus].y=i; virus[cnt_virus].x=j;
                cnt_virus++;
                map[i][j]=0;
            }
        }
    }
    combination();
} 