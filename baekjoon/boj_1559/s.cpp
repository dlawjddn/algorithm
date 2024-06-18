#include <iostream>	
#include <cstring>
#include <queue>
using namespace std;
int M, N, K;
int chToInt['W' + 1];
enum DIR {NORTH, EAST, SOUTH, WEST};
int door[100][100], box[100][100];
int vst[4][256][100][100];
struct qnode {
	int r, c, b;
};
int dr[] = { -1, 0, 1, 0 };
int dc[] = { 0, 1, 0, -1 };
int main() {
	chToInt['N'] = NORTH;
	chToInt['E'] = EAST;
	chToInt['S'] = SOUTH;
	chToInt['W'] = WEST;
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	for(int tc = 1; ; ++tc) {
		cin >> M >> N;
		if (M == 0 && N == 0) {
			break;
		}
		for (int r = 0; r < M; ++r) {
			for (int c = 0; c < N; ++c) {
				char ch;
				cin >> ch;
				door[r][c] = chToInt[ch];
			}
		}
		memset(box, -1, 100 * 100 * sizeof(int));
		cin >> K;
		for (int k = 0; k < K; ++k) {
			int r, c;
			cin >> r >> c;
			box[r - 1][c - 1] = k;
		}
		int t = 0;
		vst[3][0][0][0] = tc;
		queue<qnode> q;
		q.push({ 0, 0, 0 });
		while (!q.empty()) {
			int qs = q.size();
			while (qs--) {
				int r = q.front().r, c = q.front().c, b = q.front().b;
				q.pop();
				if (box[r][c] >= 0) {
					b = b | (1 << box[r][c]);
				}
				if (b == (1 << K) - 1 && r == M - 1 && c == N - 1) {
					goto out;
				}
				if (vst[t % 4][b][r][c] != tc) {
					vst[t % 4][b][r][c] = tc;
					q.push({ r, c, b });
				}
				int nr = r + dr[(door[r][c] + t) % 4], nc = c + dc[(door[r][c] + t) % 4];
				if (nr < 0 || M <= nr || nc < 0 || N <= nc) {
					continue;
				}
				if (vst[t % 4][b][nr][nc] != tc) {
					vst[t % 4][b][nr][nc] = tc;
					q.push({ nr, nc, b });
				}
			}
			++t;
		}
	out:
		cout << t << '\n';
	}
	return 0;
}