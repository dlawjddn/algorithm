#include <iostream>
#include <cstring>
#include <queue>
using namespace std;
queue<pair<int, int> > q;
int map[200][200][6], visited[200][200], move_x[4]={1,0,-1,0}, move_y[4]={0,1,0,-1}, size_y=0, size_x=0, second=0;
void plz(int cnt)
{
    memset(visited, 0, sizeof(visited));
    while(!q.empty())
    {
        int y=q.front().first;
        int x=q.front().second; q.pop();
        visited[y][x]=1;
        for(int d=0; d<4; d++)
        {
            int ny=y+move_y[d];
            int nx=x+move_x[d];
            if (ny>=0 && ny<size_y && nx>=0 && nx<size_x && visited[ny][nx]==0)
            visited[ny][nx]=1;
        }
    }
    for(int a=0; a<size_y; a++)
    {
        for(int b=0; b<size_x; b++)
        {
            if (visited[a][b]==1)
            map[a][b][cnt]=-1;
            else
            map[a][b][cnt]=map[a][b][cnt-1];
        }
    }
}
void make_map()
{
    for(int i=2; i<=5; i++)
    {
        for(int a=0; a<size_y; a++)
        {
            for(int b=0; b<size_x; b++)
            {
                if (i%2==0)
                {
                    if (map[a][b][i-1]==-1)
                    map[a][b][i]=i;
                    else
                    map[a][b][i]=map[a][b][i-1];
                }
                else
                {
                    if (map[a][b][i-2] == i - 3)
                    q.push(make_pair(a, b));
                }
            }
        }
        if (i%2!=0)
        plz(i);
    }
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    string s;
    cin>>size_y>>size_x>>second;
    for(int i=0; i<size_y; i++)
    {
        cin>>s;
        for(int j=0; j<size_x; j++)
        {
            if (s[j]=='O')
            map[i][j][0]=0;
            else
            map[i][j][0]=-1;
            map[i][j][1]=map[i][j][0];
        }
    }
    make_map();
    if (second<=1)
    {
        for(int a=0; a<size_y; a++)
        {
            for(int b=0; b<size_x; b++)
            {
                if (map[a][b][second]<0)
                cout<<".";
                else
                cout<<"O";
            }
            cout<<"\n";
        }
    }
    else
    {
        if (second%2==0)
        {
            for(int a=0; a<size_y; a++)
            {
                for(int b=0; b<size_x; b++)
                    cout<<"O";
                cout<<"\n";
            }
        }
        else if (second%4==1)
        {
            for(int a=0; a<size_y; a++)
            {
                for(int b=0; b<size_x; b++)
                {
                    if (map[a][b][5]<0)
                    cout<<".";
                    else
                    cout<<"O";
                }
                cout<<"\n";
            }
        }
        else if (second%4==3)
        {
            for(int a=0; a<size_y; a++)
            {
                for(int b=0; b<size_x; b++)
                {
                    if (map[a][b][3]<0)
                    cout<<".";
                    else
                    cout<<"O";
                }
                cout<<"\n";
            }
        }
    }
}