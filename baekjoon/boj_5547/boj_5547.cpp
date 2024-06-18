#include <iostream>
using namespace std;
int map[101][101], visited[101][101], move_y[6]={-1,-1,0,1,1,0}, odd_x[6]={0,1,1,1,0,-1}, even_x[6]={-1,0,1,0,-1,-1}, size_x=0, size_y=0, ans=0;
void solve()
{
    for(int y=1; y<=size_y; y++)
    {
        for(int x=1; x<=size_x; x++)
        {
            int cnt=6;
            if (map[y][x])
            {
                for(int d=0; d<6; d++)
                {
                    int ny=y+move_y[d], nx=0;
                    if (y%2==1)
                    nx=x+odd_x[d];
                    else
                    nx=x+even_x[d];
                    if (ny>0 && ny<=size_y && nx>0 && nx<=size_x && !visited[ny][nx])
                    cnt--;
                }
                ans+=cnt;
            }
        }
    }
    cout<<ans;
}
void use_dfs(int y, int x)
{
    visited[y][x]=1;
    for(int d=0; d<6; d++)
    {
        int ny=y+move_y[d], nx=0;
        if (y%2==1)
        nx=x+odd_x[d];
        else
        nx=x+even_x[d];
        if (ny>0 && ny<=size_y && nx>0 && nx<=size_x && !visited[ny][nx] && !map[ny][nx])
        use_dfs(ny, nx);
    }
}
void check_outside()
{
    for(int a=1; a<=size_x; a++)
    {
        if (!visited[1][a] && !map[1][a])
        use_dfs(1, a);
        if (!visited[size_y][a] && !map[size_y][a])
        use_dfs(size_y, a);
    }
    for(int b=1; b<size_y; b++)
    {
        if (!visited[b][1] && !map[b][1])
        use_dfs(b, 1);
        if (!visited[b][size_x] && !map[b][size_x])
        use_dfs(b, size_x);
    }
}
int main()
{
    cin>>size_x>>size_y;
    for(int i=1; i<=size_y; i++)
    {
        for(int j=1; j<=size_x; j++)
        {
            cin>>map[i][j];
        }
    }
    check_outside();
    solve();
}