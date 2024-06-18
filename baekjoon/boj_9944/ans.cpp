#define MAX 1000000
#include <iostream>
#include <algorithm>
using namespace std;
bool check[30][30];
char arr[30][30];
int row, col, result;
int dx[4] = { 0,1,0,-1 };
int dy[4] = { -1,0,1,0 };

bool can_mv(int y, int x) {
	if (x >= 0 && y >= 0 && x < col && y < row && arr[y][x] != '*' && !check[y][x]) return true;
	return false;
}

void dfs(int y, int x, int cnt) {
	if (cnt >= result) return;
	bool finish = true;
	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];
		if (can_mv(ny,nx)) {
			finish = false;
			check[ny][nx] = true;
			while (1) {
				nx += dx[i];
				ny += dy[i];
				if (can_mv(ny, nx)) 
					check[ny][nx] = true;
				else {
					nx -= dx[i];
					ny -= dy[i];
					break;
				}
			}
			dfs(ny, nx, cnt + 1);
			while (1) {
				if (nx == x && ny == y) break;
				check[ny][nx] = false;
				nx -= dx[i];
				ny -= dy[i];
			}
		}
	}
	if (finish) {
		bool fin = true;
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				if (arr[i][j] == '.' && !check[i][j]) {
					fin = false;
					break;
				}
			}
			if (!fin) break;
		}
		if (fin) {		
			result = min(result, cnt);
			return;
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	string str, buf, s;
	int t = 1;
	while (cin >> row >> col) {
		for(int i=0;i<row;i++)
			for (int j = 0; j < col; j++) {
				cin >> arr[i][j];
				check[i][j] = false;
			}
		result = MAX;
		for (int i = 0; i < row; i++)
			for (int j = 0; j < col; j++) {
				if (arr[i][j] == '.') {
					check[i][j] = true;
					dfs(i, j, 0);
					check[i][j] = false;
				}
			}
		if (result == MAX) result = -1;
		cout << "Case " << t++ << ": " << result << '\n';
	}
	return 0;
}
