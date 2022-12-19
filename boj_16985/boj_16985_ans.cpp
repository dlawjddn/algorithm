#include <bits/stdc++.h>
using namespace std;

struct Node{
	int x, y, z;
	Node() : x(0), y(0), z(0) {}
	Node(int a, int b, int c) : x(a), y(b), z(c) {}
};

int dx[] = {1, -1, 0, 0, 0, 0};
int dy[] = {0, 0, 1, -1, 0, 0};
int dz[] = {0, 0, 0, 0, 1, -1};
const int n = 5, inf = 1e9+7; //size, maximum

int input[n][n][n]; //input data
int rotated[4][n][n][n];
int mp[n][n][n]; //current map
int stackingOrder[n] = {0, 1, 2, 3, 4};

inline bool bound(int x, int y, int z){
	return 0 <= x && x < n
		&& 0 <= y && y < n
		&& 0 <= z && z < n;
}

int bfs(){
	queue<Node> q; q.push({0, 0, 0});
	int dist[n][n][n]; memset(dist, -1, sizeof(dist));

	if(mp[0][0][0] == 0 || mp[4][4][4] == 0) return inf;
	dist[0][0][0] = 0;

	while(!q.empty()){
		Node now = q.front();
		int x = now.x, y = now.y, z = now.z;
		q.pop();

		for(int i=0; i<6; i++){
			int nxtX = x + dx[i];
			int nxtY = y + dy[i];
			int nxtZ = z + dz[i];
			if(!bound(nxtX, nxtY, nxtZ)) continue;
			if(dist[nxtX][nxtY][nxtZ] != -1) continue;
			if(mp[nxtX][nxtY][nxtZ] == 0) continue;
			if(nxtX == n-1 && nxtY == n-1 && nxtZ == n-1) return dist[x][y][z] + 1;
			dist[nxtX][nxtY][nxtZ] = dist[x][y][z] + 1;
			q.push({nxtX, nxtY, nxtZ});
		}
	}
	return inf;
}

void rotating(){
	for(int i=0; i<n; i++)
		for(int j=0; j<n; j++)
			for(int k=0; k<n; k++)
				rotated[0][i][j][k] = input[i][j][k];

	for(int rot=1; rot<4; rot++){
		for(int i=0; i<n; i++){
			for(int j=0; j<n; j++){
				for(int k=0; k<n; k++){
					rotated[rot][i][j][k] = rotated[rot-1][i][k][n-1-j];
				}
			}
		}
	}
}

void stacking(int bit){
	for(int i=0; i<n; i++){
		int idx = (bit&3); bit >>= 2;
		for(int j=0; j<n; j++){
			for(int k=0; k<n; k++){
				mp[i][j][k] = rotated[idx][stackingOrder[i]][j][k];
			}
		}
	}
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	for(int i=0; i<n; i++)
		for(int j=0; j<n; j++)
			for(int k=0; k<n; k++)
				cin >> input[i][j][k];

	rotating();

	int ans = inf;

	do{
		for(int bit=0; bit<(1<<10); bit++){
			stacking(bit);
			ans = min(ans, bfs());
		}
	}while(next_permutation(stackingOrder, stackingOrder+n));

	if(ans > 1e9) ans = -1;
	cout << ans;
}
