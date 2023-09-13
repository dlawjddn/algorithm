#include<iostream>
#include<queue>
 
#define endl "\n"
#define MAX 50
using namespace std;
 
int N, M, Bit;
char MAP[MAX][MAX];
bool Visit[MAX][MAX][35];
 
int dx[] = { 0, 0, 1, -1 };
int dy[] = { 1, -1, 0, 0 };
pair<int, int> Start, End;
 
void Input()
{
    int Idx = 0;
    cin >> M >> N;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            cin >> MAP[i][j];
            if (MAP[i][j] == 'S')
            {
                Start.first = i;
                Start.second = j;
            }
            else if (MAP[i][j] == 'X')
            {
                MAP[i][j] = (Idx++) + '0';
            }
        }
    }
    
    Bit = (1 << Idx) - 1;
}
 
void Solution()
{
    queue <pair<pair<int, int>, pair<int, int> > > Q;
    Q.push(make_pair(make_pair(Start.first, Start.second), make_pair(0, 0)));
    Visit[Start.first][Start.second][0] = true;
 
    while (Q.empty() == 0)
    {
        int x = Q.front().first.first;
        int y = Q.front().first.second;
        int Cnt = Q.front().second.first;
        int Bit_State = Q.front().second.second;
        Q.pop();
 
        if (MAP[x][y] == 'E' && Bit_State == Bit)
        {
            cout << Cnt << endl;
            return;
        }
 
        for(int i = 0 ; i < 4; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];
            int nB = Bit_State;
 
            if (nx >= 0 && ny >= 0 && nx < N && ny < M)
            {
                if ('0' <= MAP[nx][ny] && MAP[nx][ny] < '5')
                {
                    nB = Bit_State | (1 << MAP[nx][ny] - '0');
                    if (Visit[nx][ny][nB] == false)
                    {
                        Visit[nx][ny][nB] = true;
                        Q.push(make_pair(make_pair(nx, ny), make_pair(Cnt + 1, nB)));
                    }
                }
                else if (MAP[nx][ny] != '#')
                {
                    if (Visit[nx][ny][nB] == false)
                    {
                        Visit[nx][ny][nB] = true;
                        Q.push(make_pair(make_pair(nx, ny), make_pair(Cnt + 1, nB)));
                    }
                }
            }
        }
    }
}
 
void Solve()
{
    Input();
    Solution();
}
 
int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
 
    //freopen("Input.txt", "r", stdin);
    Solve();
 
    return 0;
}
