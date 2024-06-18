#include <stdio.h>
int map[1000][1000], visited[1000][1000], move_x[4]={1,0,-1,0}, move_y[4]={0,1,0,-1}, size=0, front=0, rear=0, right_dest=0, ans=0;
long long dp[1000][1000];
typedef struct _Point
{
    int x, y;
}Point;
Point queue[1000000], start;
void enqueue(Point n)
{
    queue[rear++]=n;
}
Point dequeue()
{
    return queue[front++];
}
void set_up()
{
    int dis_c=0, dis_r=0;
    for(int a=0; a<size; a++)
    {
        if (map[0][a] == 1)
        dis_c=1;
        if (map[a][0] == 1)
        dis_r=1;
        if (dis_c == 1)
        dp[0][a]=0;
        else
        dp[0][a]=1;
        if (dis_r == 1)
        dp[a][0] = 0;
        else
        dp[a][0] = 1;
    }
}
long long check_dp()
{
    set_up();
    for(int a=1; a<size; a++)
    {
        for(int b=1; b<size; b++)
        {
            if (map[a][b] == 1)
            dp[a][b] = 0;
            else
            dp[a][b] = dp[a][b-1] + dp[a-1][b];
            dp[a][b]%=2147483647;
        }
    }
    return dp[size-1][size-1];
}
int use_bfs()
{
    Point temp, next;
    while (front<rear)
    {
        temp=dequeue();
        if (temp.y == size-1 && temp.x==size-1)
        return 1;
        for(int q=0; q<4; q++)
        {
            next.x=temp.x+move_x[q];
            next.y=temp.y+move_y[q];
            if (next.x>=0 && next.x<size && next.y>=0 && next.y<size && visited[next.y][next.x]==0 && map[next.y][next.x]==0)
            {
                enqueue(next);
                visited[next.y][next.x]=1;
            }
        }
    }
    return 0;
}
int main()
{
    char str[1001];
    scanf("%d", &size);
    for(int i=0; i<size; i++)
    {
        scanf("%s", str);
        for(int j=0; j<size; j++)
        {
            if (str[j] == '.')
            map[i][j]=0;
            else
            map[i][j]=1;
        }
    }
    start.y=0;
    start.x=0;
    enqueue(start);
    visited[start.y][start.x]=1;
    right_dest=use_bfs();
    if (!right_dest)
    printf("INCONCEIVABLE");
    else
    {
        ans = check_dp();
        if (ans == 0)
        printf("THE GAME IS A LIE");
        else
        printf("%lld", ans);
    }
}