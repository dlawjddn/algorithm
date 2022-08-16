#include <iostream>
using namespace std;
char map[501][501];
int visited[501][501], size_x=0, size_y=0, cnt=0, flag=0;
void use_dfs(int y, int x)
{
    int ny=0, nx=0;
    visited[y][x]=1;
    if (map[y][x]=='R')
        ny=y, nx=x+1;
    else if (map[y][x]=='L')
        ny=y, nx=x-1;
    else if (map[y][x]=='D')
        ny=y+1, nx=x;
    else
        ny=y-1, nx=x;
    if (ny>=0 && ny<size_y && nx>=0 && nx<size_x)
    {
        if (visited[ny][nx]==0)
        use_dfs(ny, nx);
        else if (visited[ny][nx]==1)
        flag=1;
        else if (visited[ny][nx]==2)
        {
            flag=2;
            cnt++;
        }
    }
    else
    {
        visited[y][x]+=1;
        flag=2;
        cnt++;
        return ;
    }
    if (flag)
    {
        if (flag==2)
        visited[y][x]+=1;
        return ;
    }
}
void solve()
{
    for(int a=0; a<size_y; a++)
    {
        for(int b=0; b<size_x; b++)
        {
            flag=0;
            if (visited[a][b]==0)
            use_dfs(a, b);
            else if (visited[a][b]==2)
            cnt++;
            else
            continue;
        }
    }
    cout<<cnt;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin>>size_y>>size_x;
    for(int i=0; i<size_y; i++)
    {
        for(int j=0; j<size_x; j++)
        {
            cin>>map[i][j];
        }
    }
    solve();
}