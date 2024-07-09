#include <iostream>
#include <cmath>
#include <cstring>
#include <queue>
using namespace std;
struct Point
{
    int x, y;
};
Point virus[10];
int map[50][50], temp_map[50][50], visited[50][50], arr[10], move_x[4]={1,0,-1,0}, move_y[4]={0,1,0,-1}, size_sq=0, max_virus=0, virus_cnt=0, emp_cnt=0, ans=987654321;
void spread_virus()
{
    Point temp, next;
    int total_time=0, temp_cnt=0, temp_max=1;
    queue<Point> q;
    for(int a=0; a<max_virus; a++)
    {
        q.push(virus[arr[a]]);
        visited[virus[arr[a]].y][virus[arr[a]].x]=1;
    }
    while(!q.empty())
    {
        temp=q.front(); q.pop();
        total_time=visited[temp.y][temp.x];
        for(int d=0; d<4; d++)
        {
            next.y=temp.y+move_y[d];
            next.x=temp.x+move_x[d];
            if (next.y>=0 && next.y<size_sq && next.x>=0 && next.x<size_sq && visited[next.y][next.x]==0 && map[next.y][next.x]!=1)
            {
                visited[next.y][next.x]=visited[temp.y][temp.x]+1;
                temp_cnt++;
                q.push(next);
            }
        }
    }
    if (temp_cnt==emp_cnt)
    {
        for(int a=0; a<size_sq; a++)
        {
            for(int b=0; b<size_sq; b++)
            {
                if (map[a][b]!=2)
                temp_max=max(temp_max, visited[a][b]);
            }
        }
        ans=min(ans, temp_max);
    }

}
void find_out(int idx, int num)
{
    if(idx==max_virus-1)
    {
        spread_virus();
        memset(visited, 0, sizeof(visited));
        return ;
    }
    else
    {
        idx++;
        for(int b=num+1; b<virus_cnt; b++)
        {
            arr[idx]=b;
            find_out(idx, b);
        }
    }
}
void combination()
{
    int idx=0;
    for(int i=0; i<virus_cnt; i++)
    {
        arr[idx]=i;
        find_out(idx, i);
    }
    if (ans==987654321)
    cout<<"-1";
    else
    cout<<ans-1;
}
int main()
{
    int temp_empty=0;
    cin>>size_sq>>max_virus;
    for(int i=0; i<size_sq; i++)
    {
        for(int j=0; j<size_sq; j++)
        {
            cin>>map[i][j];
            if (map[i][j]==2)
            {
                virus[virus_cnt].y=i; virus[virus_cnt].x=j;
                virus_cnt++;
                temp_empty++;
            }
            else if (map[i][j]==0)
            temp_empty++;
        }
    }
    emp_cnt=temp_empty-max_virus;
    combination();
}