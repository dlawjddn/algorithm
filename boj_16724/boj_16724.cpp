#include <iostream>
using namespace std;
char map[1001][1001];
int visited[1001][1001], size_x=0, size_y=0, cnt=0;
void use_dfs(int y, int x)
{
    int ny=0, nx=0;
    visited[y][x]=1;
    if (map[y][x]=='D')
    ny=y+1, nx=x;
    else if (map[y][x]=='U')
    ny=y-1, nx=x;
    else if (map[y][x]=='R')
    ny=y, nx=x+1;
    else
    ny=y, nx=x-1;
    if (visited[ny][nx]==0)
    use_dfs(ny, nx);
    else if (visited[ny][nx]==1)
    cnt++;
    visited[y][x]=2;
}
void solve()
{
    for(int a=0; a<size_y; a++)
    {
        for(int b=0; b<size_x; b++)
        {
            if (visited[a][b]==0)
                use_dfs(a, b);
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