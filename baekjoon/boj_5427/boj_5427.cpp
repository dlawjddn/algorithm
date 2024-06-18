#include <iostream>
#include <cstring>
#include <queue>
using namespace std;
char map[1001][1001];
int visited[1000][1000], move_x[4]={1,0,-1,0}, move_y[4]={0,1,0,-1}, test=0, size_y=0, size_x=0, ans=0;
struct Point
{
    int x, y, cnt;
};
Point start, fire;
queue<Point> q;
int use_bfs()
{
    Point temp, next;
    q.push(start);
    visited[start.y][start.x]=1;
    while(!q.empty())
    {
        temp=q.front(); q.pop();
        for(int d=0; d<4; d++)
        {
            next.y=temp.y+move_y[d]; next.x=temp.x+move_x[d]; next.cnt=temp.cnt;
            if (next.y>=0 && next.y<size_y && next.x>=0 && next.x<size_x && visited[next.y][next.x]==0 && map[next.y][next.x]!='#')
            {
                if (next.cnt==-1)
                {
                    q.push(next);
                    visited[next.y][next.x]=-1;
                }
                else
                {
                    next.cnt+=1;
                    q.push(next);
                    visited[next.y][next.x]=1;
                }
            }
            if (next.y<0 || next.y>=size_y || next.x<0 || next.x>=size_x)
            {
                if (next.cnt==-1)
                continue;
                else
                return next.cnt+1;
            }
        }
    }
    return -1;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin>>test;
    for(int i=0; i<test; i++)
    {
        string s;
        cin>>size_x>>size_y;;
        for(int a=0; a<size_y; a++)
        {
            cin>>s;
            for(int b=0; b<size_x; b++)
            {
                map[a][b]=s[b];
                if (map[a][b]=='@')
                {
                    start.y=a; start.x=b, start.cnt=0;
                }
                else if (map[a][b]=='*')
                {
                    fire.y=a; fire.x=b, fire.cnt=-1;
                    visited[fire.y][fire.x]=-1;
                    q.push(fire);
                }
            }
        }
        ans = use_bfs();
        if (ans==-1)
        cout<<"IMPOSSIBLE\n";
        else
        cout<<ans<<"\n";
        while(!q.empty()) q.pop();
        memset(visited, 0, sizeof(visited));
    }
}