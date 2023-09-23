#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <queue>
using namespace std;

int main() {
	cin.sync_with_stdio(false);
	cin.tie(nullptr);
	
	int N, M;
	cin >> N >> M;
	
	char bo[50][51];
	int sx, sy;
	for (int i = 0; i < N; ++i) {
		cin >> bo[i];
		for (int j = 0; j < M; ++j) if (bo[i][j] == 'S') {
			sx = i;
			sy = j;
		}
	}
	
	pair<int, int> dist[50][50];
	fill(dist[0] + 0, dist[49] + 50, make_pair(0x3f3f3f3f, 0x3f3f3f3f));
	dist[sx][sy] = { 0, 0 };
	
	priority_queue<tuple<int, int, int, int>, vector<tuple<int, int, int, int>>, greater<>> PQ;
	PQ.emplace(0, 0, sx, sy);
	
	while (!PQ.empty()) {
		auto [a, b, x, y] = PQ.top(); PQ.pop();
		if (bo[x][y] == 'F') return cout << a << ' ' << b, 0;
		if (dist[x][y] < make_pair(a, b)) continue;
		
		for (int i = 0; i < 4; ++i) {
			int nx = x + "0121"[i] - 49;
			int ny = y + "1210"[i] - 49;
			if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue;
			
			int na = a + (bo[nx][ny] == 'g');
			int cnt = 0;
			for (int j = 0; j < 4; ++j) {
				int nnx = nx + "0121"[j] - 49;
				int nny = ny + "1210"[j] - 49;
				if (nnx < 0 || nnx >= N || nny < 0 || nny >= M) continue;
				cnt += bo[nnx][nny] == 'g';
			}
			int nb = b + (bo[nx][ny] == '.' && cnt > 0);
			if (dist[nx][ny] <= make_pair(na, nb)) continue;
			
			dist[nx][ny] = { na, nb };
			PQ.emplace(na, nb, nx, ny);
		}
	}

	return 0;
}