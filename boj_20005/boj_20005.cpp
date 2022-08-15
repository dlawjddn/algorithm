#include <iostream>
#include <cstring>
#include <queue>
using namespace std;
char map[1001][1001];
int visited[1000][1000], move_x[4]={1,0,-1,0}, move_y[4]={0,1,0,-1}, demage[26], dist[26], size_x=0, size_y=0, boss_hp=0, dps=0, player=0, cnt=0;
queue<pair<int, int> > q;
struct Point
{
	int x, y;
};
Point player_pos[26];
void use_bfs(int a)
{
	int stop=0;
	while(!q.empty())
	{
		int temp_y=q.front().first;
		int temp_x=q.front().second; q.pop();
		if (stop)
		{
			while(!q.empty())
			q.pop();
		}
		for(int d=0; d<4; d++)
		{
			int next_x=temp_x+move_x[d];
			int next_y=temp_y+move_y[d];
			if (stop)
			break;
			{ 
				if (next_x>=0 && next_x<size_x && next_y>=0 && next_y<size_y && visited[next_y][next_x]==0 && map[next_y][next_x]!='X')
				{
					if (map[next_y][next_x]=='B')
					{
						dist[a]=visited[temp_y][temp_x];
						stop=1;
					}
					else
					{
						if (stop)
						break;
						visited[next_y][next_x]=visited[temp_y][temp_x]+1;
						q.push(make_pair(next_y, next_x));
					}
				}
			}
		}
	}
}
void find_dist()
{
	for(int a=0; a<player; a++)
	{
		q.push(make_pair(player_pos[a].y, player_pos[a].x));
		visited[player_pos[a].y][player_pos[a].x]=1;
		use_bfs(a);
		memset(visited, 0, sizeof(visited));
	}
}
int main()
{
	string str;
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin>>size_y>>size_x>>player;
	for(int i=0; i<size_y; i++)
	{
		cin>>str;
		for(int j=0; j<size_x; j++)
		{
			map[i][j]=str[j];
			if (map[i][j] >= 'a' && map[i][j] <= 'z')
			{
				player_pos[map[i][j]-'a'].y=i;
				player_pos[map[i][j]-'a'].x=j;
			}
		}
	}
	for(int k=0; k<player; k++)
	{
		char c;
		int num;
		cin>>c>>num;
		demage[c-'a']=num;
	}
	cin>>boss_hp;
	find_dist();
	while(boss_hp>0)
	{
		for(int a=0; a<player; a++)
		{
			dist[a]-=1;
			if (dist[a]==0)
			{
				dps+=demage[a];
				cnt++;
			}
		}
		boss_hp-=dps;
	}
	cout<<cnt;
}