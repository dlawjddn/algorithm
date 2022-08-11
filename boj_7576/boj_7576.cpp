#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;
queue<pair<int, int> > q;
int map[1000][1000], visited[1000][1000], move_x[4]={1,0,-1,0}, move_y[4]={0,1,0,-1}, x_size=0, y_size=0, ans=0;
void use_bfs()
{
    pair<int, int> temp;
    while(!q.empty())
    {
        temp=q.front();
        q.pop();
        for(int d=0; d<4; d++)
        {
            int next_y=temp.first+move_y[d];
            int next_x=temp.second+move_x[d];
            if (next_y>=0 && next_y<y_size && next_x>=0 && next_x<x_size && visited[next_y][next_x]==0)
            {
                q.push(make_pair(next_y, next_x));
                visited[next_y][next_x]=visited[temp.first][temp.second]+1;
            }
        }
    }
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> x_size >> y_size;
    for(int i=0; i<y_size; i++)
    {
        for(int j=0; j<x_size; j++)
        {
            cin>>map[i][j];
            if (map[i][j]==1)
            {
                visited[i][j]=1;
                q.push(make_pair(i, j));
            }
            else if (map[i][j]==-1)
            visited[i][j]=-1;
        }
    }
    use_bfs();
    for(int a=0; a<y_size; a++)
    {
        for(int b=0; b<x_size; b++)
        {
            if (visited[a][b]>0 && ans<visited[a][b])
            ans=visited[a][b];
            else if (visited[a][b]==0)
            ans=987654321;
        }
    }
    if (ans == 987654321)
    cout<<"-1";
    else
    cout<<ans-1;
}