#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
int map[20][20], visited[20][20], move_x[4]={-1,0,0,1}, move_y[4]={0,-1,1,0}, size_sq=0, time_cnt=0, start_y=0, start_x=0, shark_size=2, eating_cnt=0;
int selcet_fish()
{
    int min_x=0, min_y=0, min_time=987654321;
    for(int a=0; a<size_sq; a++)
    {
        for(int b=0; b<size_sq; b++)
        {
            if (map[a][b]<shark_size && map[a][b]>0 && visited[a][b]>0)
            {
                if (min_time>visited[a][b])
                {
                    min_time=visited[a][b];
                    min_y=a; min_x=b;
                }
            }
        }
    }
    if (min_time==987654321)
    return -1;
    else
    {
        start_y=min_y; start_x=min_x;
        if (eating_cnt==shark_size-1)
        {
            eating_cnt=0;
            shark_size++;
        }
        else eating_cnt++;
        return min_time-1;
    }
}
void check_distance()
{
    queue<pair<int, int> > q;
    q.push(make_pair(start_y, start_x));
    visited[start_y][start_x]=1;
    map[start_y][start_x]=0;
    while(!q.empty())
    {
        int y=q.front().first, x=q.front().second; q.pop();
        for(int d=0; d<4; d++)
        {
            int ny=y+move_y[d], nx=x+move_x[d];
            if (ny>=0 && ny<size_sq && nx>=0 && nx<size_sq && !visited[ny][nx] && map[ny][nx]<=shark_size)
            {
                if (map[ny][nx]==shark_size || map[ny][nx]==0)
                {
                    visited[ny][nx]=visited[y][x]+1;
                    q.push(make_pair(ny, nx));
                }
                else visited[ny][nx]=visited[y][x]+1;
            }
        }
    }
}
void solve()
{
    while(1)
    {
        check_distance();
        int temp_time=selcet_fish();
        if (temp_time==-1) break;
        else time_cnt+=temp_time;
        memset(visited, 0, sizeof(visited));
    }
    cout<<time_cnt;
}
int main()
{
    cin>>size_sq;
    for(int i=0; i<size_sq; i++)
    {
        for(int j=0; j<size_sq; j++)
        {
            cin>>map[i][j];
            if (map[i][j]==9)
            start_y=i; start_x=j;
        }
    }
    solve();
}