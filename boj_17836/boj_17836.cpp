#include <iostream>
#include <queue>
#include <cmath>
using namespace std;
queue<pair<int, int> > q;
int map[101][101], visited[101][101], move_x[4]={1,0,-1,0}, move_y[4]={0,1,0,-1}, size_x=0, size_y=0, limit_time=0, gram_x=0, gram_y=0;
void use_gram()
{
    int abs_dist=abs(size_y-gram_y)+abs(size_x-gram_x);
    if (visited[size_y][size_x]==0) visited[size_y][size_x]=visited[gram_y][gram_x]+abs_dist;
    else
    {
        if (visited[size_y][size_x]>visited[gram_y][gram_x]+abs_dist)
        visited[size_y][size_x]=visited[gram_y][gram_x]+abs_dist;
    }
}
void use_bfs()
{
    q.push(make_pair(1, 1));
    visited[1][1]=1;
    while(!q.empty())
    {
        int y=q.front().first, x=q.front().second; q.pop();
        for(int d=0; d<4; d++)
        {
            int ny=y+move_y[d], nx=x+move_x[d];
            if (ny>0 && ny<=size_y && nx>0 && nx<=size_x && !visited[ny][nx] && map[ny][nx]!=1)
            {
                visited[ny][nx]=visited[y][x]+1;
                q.push(make_pair(ny, nx));
            }
        }
    }
    if (visited[gram_y][gram_x]) use_gram();
}
int main()
{
    cin>>size_y>>size_x>>limit_time;
    for(int i=1; i<=size_y; i++)
    {
        for(int j=1; j<=size_x; j++)
        {
            cin>>map[i][j];
            if (map[i][j]==2)
            {
                gram_y=i; gram_x=j;
            }
        }
    }
    use_bfs();
    if (visited[size_y][size_x]==0 || visited[size_y][size_x]-1>limit_time) cout<<"Fail";
    else cout<<visited[size_y][size_x]-1;
}