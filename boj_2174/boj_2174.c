#include <stdio.h>
int map[101][101], move_x[4]={0,1,0,-1}, move_y[4]={-1,0,1,0}, num_robot=0, num_order=0, size_x=0, size_y=0, front=0, rear=0;
typedef struct _Point
{
    int x, y;
    char dir;
}Point;
typedef struct _Order
{
    int robot, repeat;
    char recife;
}Moving;
Moving order[101]; 
Point info_robot[101];
int execute(int n)
{
    int define=0;
    Point temp, next;
    for(int a=0; a<order[n].repeat; a++)
    {
        temp.x=info_robot[order[n].robot].x;
        temp.y=info_robot[order[n].robot].y;
        temp.dir=info_robot[order[n].robot].dir;
        if (order[n].recife == 'F')
        {
            if (info_robot[order[n].robot].dir == 'N')
            {
                next.x=temp.x+move_x[0];
                next.y=temp.y+move_y[0];
                next.dir=temp.dir;
                if (next.y<=0 || next.y>size_y || next.x<=0 || next.x>size_x)
                {
                    printf("Robot ");
                    printf("%d ", order[n].robot);
                    printf("crashes into the wall");
                    define=1;
                    break;
                }
                if (map[next.y][next.x]!=0)
                {
                    printf("Robot ");
                    printf("%d ", order[n].robot);
                    printf("crashes into robot %d", map[next.y][next.x]);
                    define=1;
                    break;
                }
                if (next.y>0 && next.y<=size_y && next.x>0 && next.x<=size_x && map[next.y][next.x]==0)
                {
                    info_robot[order[n].robot].x=next.x;
                    info_robot[order[n].robot].y=next.y;
                    info_robot[order[n].robot].dir=next.dir;
                    map[next.y][next.x]=map[temp.y][temp.x];
                    map[temp.y][temp.x]=0;
                }
            }
            else if (info_robot[order[n].robot].dir == 'E')
            {
                next.x=temp.x+move_x[1];
                next.y=temp.y+move_y[1];
                next.dir=temp.dir;
                if (next.y<=0 || next.y>size_y || next.x<=0 || next.x>size_x)
                {
                    printf("Robot ");
                    printf("%d ", order[n].robot);
                    printf("crashes into the wall");
                    return 0;
                }
                if (map[next.y][next.x]!=0)
                {
                    printf("Robot ");
                    printf("%d ", order[n].robot);
                    printf("crashes into robot %d", map[next.y][next.x]);
                    return 0;
                }
                if (next.y>0 && next.y<=size_y && next.x>0 && next.x<=size_x && map[next.y][next.x]==0)
                {
                    info_robot[order[n].robot].x=next.x;
                    info_robot[order[n].robot].y=next.y;
                    info_robot[order[n].robot].dir=next.dir;
                    map[next.y][next.x]=map[temp.y][temp.x];
                    map[temp.y][temp.x]=0;
                }
            }
            else if (info_robot[order[n].robot].dir == 'S')
            {
                next.x=temp.x+move_x[2];
                next.y=temp.y+move_y[2];
                next.dir=temp.dir;
                if (next.y<=0 || next.y>size_y || next.x<=0 || next.x>size_x)
                {
                    printf("Robot ");
                    printf("%d ", order[n].robot);
                    printf("crashes into the wall");
                    return 0;
                }
                if (map[next.y][next.x]!=0)
                {
                    printf("Robot ");
                    printf("%d ", order[n].robot);
                    printf("crashes into robot %d", map[next.y][next.x]);
                    return 0;
                }
                if (next.y>0 && next.y<=size_y && next.x>0 && next.x<=size_x && map[next.y][next.x]==0)
                {
                    info_robot[order[n].robot].x=next.x;
                    info_robot[order[n].robot].y=next.y;
                    info_robot[order[n].robot].dir=next.dir;
                    map[next.y][next.x]=map[temp.y][temp.x];
                    map[temp.y][temp.x]=0;
                }
            }
            else
            {
                next.x=temp.x+move_x[3];
                next.y=temp.y+move_y[3];
                next.dir=temp.dir;
                if (next.y<=0 || next.y>size_y || next.x<=0 || next.x>size_x)
                {
                    printf("Robot ");
                    printf("%d ", order[n].robot);
                    printf("crashes into the wall");
                    return 0;
                }
                if (map[next.y][next.x]!=0)
                {
                    printf("Robot ");
                    printf("%d ", order[n].robot);
                    printf("crashes into robot %d", map[next.y][next.x]);
                    return 0;
                }
                if (next.y>0 && next.y<=size_y && next.x>0 && next.x<=size_x && map[next.y][next.x]==0)
                {
                    info_robot[order[n].robot].x=next.x;
                    info_robot[order[n].robot].y=next.y;
                    info_robot[order[n].robot].dir=next.dir;
                    map[next.y][next.x]=map[temp.y][temp.x];
                    map[temp.y][temp.x]=0;
                }
            }
        }
        else if (order[n].recife == 'R')
        {
            if (temp.dir == 'N')
            info_robot[order[n].robot].dir ='E';
            else if (temp.dir == 'E')
            info_robot[order[n].robot].dir ='S';
            else if (temp.dir == 'S')
            info_robot[order[n].robot].dir = 'W';
            else
            info_robot[order[n].robot].dir ='N';
        }
        else if (order[n].recife == 'L')
        {
            if (temp.dir == 'N')
            info_robot[order[n].robot].dir ='W';
            else if (temp.dir == 'W')
            info_robot[order[n].robot].dir ='S';
            else if (temp.dir == 'S')
            info_robot[order[n].robot].dir = 'E';
            else
            info_robot[order[n].robot].dir ='N';
        }
    }
    if (define ==1)
    return 0;
    else
    return 1;
}
int main()
{
    int check=99;
    scanf("%d %d", &size_x, &size_y);
    scanf("%d %d", &num_robot, &num_order);
    for(int i=1; i<=num_robot; i++)
    {
        scanf("%d %d %c", &info_robot[i].x, &info_robot[i].y, &info_robot[i].dir);
        info_robot[i].y=size_y+1-info_robot[i].y;
        map[info_robot[i].y][info_robot[i].x]=i;
    }
    for(int j=1; j<=num_order; j++)
    {
        scanf("%d %c %d", &order[j].robot, &order[j].recife, &order[j].repeat);   
    }
    for(int k=1; k<=num_order; k++)
    {
        check=execute(k);
        if (check==0)
        break;
    }
    if (check!=0)
    printf("OK");
}