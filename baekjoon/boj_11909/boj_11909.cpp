#include <iostream>
#include <algorithm>
#include <queue>
#include <cmath>
using namespace std;
int map[2223][2223], visited[2223][2223], moveX[2]={1,0}, moveY[2]={0,1}, amp=0;
void useDP(){
    for(int i=1; i<=amp; i++){
        for(int j=1; j<=amp; j++){
            int diff1 = 0;
			int diff2 = 0;
			if (j > 1) diff1 = (map[i][j] < map[i][j - 1]) ? 0 : map[i][j] - map[i][j - 1] + 1;
			if (i > 1) diff2 = (map[i][j] < map[i - 1][j]) ? 0 : map[i][j] - map[i - 1][j] + 1;
			if (i == 1) visited[i][j] = visited[i][j - 1] + diff1;
			else if (j == 1) visited[i][j] = visited[i - 1][j] + diff2;
			else visited[i][j] = min(visited[i][j - 1] + diff1, visited[i - 1][j] + diff2);
        }
    }
}
int main(){
    cin.tie(0); cout.tie(0); ios::sync_with_stdio(0);
    cin>>amp;
    for(int i=1; i<=amp; i++){
        for(int j=1; j<=amp; j++){
            cin>>map[i][j];
            visited[i][j]=987654321;
        }
    }
    useDP();
    cout<<visited[amp][amp];
}